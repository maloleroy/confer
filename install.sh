#!/usr/bin/env bash

REPO_URL=https://github.com/maloleroy/confer.git

color_faint="\033[2m"
color_none="\033[0m"
color_bold_green="\033[1;32m"
color_blue="\033[1;94m"
color_red="\033[31m"

# Assert that git is installed
if ! command -v git &> /dev/null; then
    echo -e "git could not be found. Please install git to proceed."
    exit 1
fi

# Check if env variables are already set
if [ -n "$CONFER_PATH" ]; then
    if [ ! -d "$CONFER_PATH/.git" ]; then
        echo -e "${color_red}Broken install: CONFER_PATH defined but not a git repository.${color_none}"
        echo -e "${color_red}Please remove the CONFER_PATH variable from your environment.${color_none}"
        echo -e "${color_red}and run the install script again.${color_none}"
        exit 1
    fi
    CONFER_COMMIT=$(git -C "$CONFER_PATH" rev-parse HEAD | cut -c 1-7)
    echo -e "${color_bold_green}Confer version ${CONFER_COMMIT} is already installed in ${CONFER_PATH}${color_none}"
    # Ask the user if they want to update
    read -r -p "Do you want to update it? (y/n) " UPDATE
    if [[ "$UPDATE" =~ ^[Yy]$ ]]; then
        echo -e "\n${color_blue}Updating Confer...${color_none}${color_faint}"
        cd "$CONFER_PATH" || exit 1
        git pull || {
            echo "${color_none}${color_red}Failed to update the repository. Please check your internet connection and try again.${color_none}"
            exit 1
        }
        echo -e "\n${color_none}${color_bold_green}Confer updated to version ${CONFER_COMMIT}${color_none}"
        exit 0
    else
        echo -e "${color_faint}Skipping update.${color_none}"
    fi
    exit 0
fi

# Echo a fancy multiline message
echo -e "\033[1;32m
  _________  _  _____________
 / ___/ __ \/ |/ / __/ __/ _ \\
/ /__/ /_/ /    / _// _// , _/
\___/\____/_/|_/_/ /___/_/|_|
\033[0m
Enter the installation directory:

1) Current directory (default - just press enter)
2) System-wide installation (requires root privileges)
3) User-specific installation (home directory)
4) Custom directory (enter path)
5) Cancel installation"
read -r INSTALL_TYPE
if [ -z "$INSTALL_TYPE" ]; then
    INSTALL_TYPE=1
fi

SUDO_OR_NOT=""
if [ "$INSTALL_TYPE" == "2" ]; then
    if [ "$(id -u)" -ne 0 ]; then
        echo -e "${color_red}You need to run this script with root privileges.${color_none}"
        exit 1
    fi
fi

if [ "$INSTALL_TYPE" == "1" ]; then
    INSTALL_DIR=$(pwd)
elif [ "$INSTALL_TYPE" == "2" ]; then
    INSTALL_DIR="/usr/local/confer"
elif [ "$INSTALL_TYPE" == "3" ]; then
    INSTALL_DIR="$HOME/.confer"
elif [ "$INSTALL_TYPE" == "4" ]; then
    read -r -p "Enter the custom installation directory: " INSTALL_DIR
    if [ -z "$INSTALL_DIR" ]; then
        echo "${color_red}No directory provided. Exiting.${color_none}"
        exit 1
    fi
    # Create the directory if it doesn't exist
    mkdir -p "$INSTALL_DIR"
    if [ ! -d "$INSTALL_DIR" ]; then
        echo -e "${color_red}Failed to create the directory $INSTALL_DIR.${color_none}"
        echo "Please check your permissions."
        exit 1
    fi
elif [ "$INSTALL_TYPE" == "5" ]; then
    echo "Installation cancelled."
    exit 0
else
    echo "Invalid option. Please try again."
    exit 1
fi

echo -e "${color_blue}Installing in $INSTALL_DIR...${color_none}${color_faint}"

# Clone the repository
cd "$INSTALL_DIR" || exit
git clone ${REPO_URL} . || {
    echo "Failed to clone the repository. Please check your internet connection and try again."
    exit 1
}

COMMIT=$(git rev-parse HEAD | cut -c 1-7)

echo -e "\n${color_blue}Confer version $COMMIT${color_none}\n"

add_variables_in_rc_file() {
        if [ -f $1 ]; then
        echo "Adding environment variables to $1..."
    else
        echo "Creating $1..."
        touch $1
    fi
    {
        echo "export CONFER_PATH=$INSTALL_DIR"
        echo "export CONFER_COMMIT=$COMMIT"
        echo "alias confer='$INSTALL_DIR/confer.py'"
    } >> $1 || {
        echo -e "${color_red}Failed to add environment variables to $1${color_none}"
        echo "Please add the following lines manually:"
        echo "export CONFER_PATH=$INSTALL_DIR"
        echo "export CONFER_COMMIT=$COMMIT"
        echo "alias confer='$INSTALL_DIR/confer.py'"
        echo "If you are using a different shell, please add these lines to your shell's configuration file."
        exit 1
    }
}

# Ask the user if they want to add environment variables to .bashrc and .zshrc
read -r -p "Do you want to add environment variables to .bashrc and .zshrc? (y/n) " ADD_ENV_VARS
if [[ "$ADD_ENV_VARS" =~ ^[Yy]$ ]]; then
    if command -v zsh &> /dev/null; then
        add_variables_in_rc_file ~/.zshrc
        VARS_ADDED=1
    else
        echo "zsh is not installed. Skipping .zshrc configuration."
    fi
    if command -v bash &> /dev/null; then
        add_variables_in_rc_file ~/.bashrc
        VARS_ADDED=1
    else
        echo "bash is not installed. Skipping .bashrc configuration."
    fi
    if [ "$VARS_ADDED" ]; then
        echo -e "${color_bold_green}Environment variables added!${color_none}"
        echo "Restart your terminal or run 'source ~/.bashrc' or 'source ~/.zshrc' for the changes to take effect."
    else
        echo -e "${color_red}No supported shell configuration files found. Please add the environment variables manually.${color_none}"
    fi
else
    echo -e "${color_faint}Skipping environment variable addition.${color_none}\n"
    echo "Consider setting the following variables/alias manually:"
    echo "export CONFER_PATH=$INSTALL_DIR"
    echo "export CONFER_COMMIT=$COMMIT"
    echo "alias cf='$INSTALL_DIR/cf.py'"
fi

echo -e "\n${color_bold_green}Installation complete! Have fun using Confer!${color_none}"