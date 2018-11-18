# First install 3.7.0 binary to make pipenv pythonm with
pyenv install 3.7.0

# Install pipenv
brew install pipenv
# Install env
pipenv install 3.7.0

cd controller/Keyboards 
pipenv install --python ~/.pyenv/versions/3.7.0/bin/python
# pipenv install --skip-lock --python ~/.pyenv/versions/3.7.0/bin/python
pipenv shell
./ergodox.bash
