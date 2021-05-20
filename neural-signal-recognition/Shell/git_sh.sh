
function init() {
	git remote set-url origin git@github.com:junyoung-sim/neural-signal-recognition-dnn
}

function upload() {
	git add -A
	git commit -am "Automatic Update from Bash"
	git push
}

function download() {
	git pull
}
