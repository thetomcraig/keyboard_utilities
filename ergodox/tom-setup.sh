brew tap ArmMbed/homebrew-formulae
brew tap arm-none-eabi-gcc
brew install pipenv
brew install cmake
brew install ctags

cd controller/Keyboards 
pipenv install --skip-lock --python ~/.pyenv/versions/3.7.0/bin/python

pipenv shell
pip install kll
./ergodox.bash
