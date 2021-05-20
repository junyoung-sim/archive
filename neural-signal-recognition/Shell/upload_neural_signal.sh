# Shell script to upload a new neural signal dataset
# to the Neural Signal Data Archive

# Type in the path to the repository when using command via terminal
function upload_ns() {
	PATH_TO_REPOS=$1
	PATH_TO_SHELL=/Shell/

	cd $1$PATH_TO_SHELL
	python upload_neural_signal.py
}
