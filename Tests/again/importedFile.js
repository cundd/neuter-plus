window.again = window.again || {}
if (window.again.importedFile) {
	throw "File imported twice";
}
window.again.importedFile = true;
window.fileCounter++;