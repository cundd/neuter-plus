/**
 * Created by daniel on 27/12/13.
 */

window = typeof window !== 'undefined' ? window : global;
window.fileCounter = 0;
var fileCounterExpected = 16;

(function() {/*require('importedFile1.js');// */

window.importedFile1 = true;
console.log('Imported importedFile1.js');
window.fileCounter++;

})();


(function() {/*require('importedFile2');// */

window.importedFile2 = true;
console.log('Imported importedFile2.js');
window.fileCounter++;

})();


(function() {/*require('importedFileWithSubRequire');// */

console.log('Imported importedFileWithSubRequire.js');
(function() {/*require('subRequiredFile1');// */

window.subRequiredFile = true;
console.log('Imported subRequiredFile1.js');
window.fileCounter++;

})();


(function() {/*require('subRequiredFile2.js');// */

window.subRequiredFile = true;
console.log('Imported subRequiredFile2.js');
window.fileCounter++;

})();


window.fileCounter++;

})();


(function() {/*require('importNested');// */

window.nested = {};
(function() {/*require('nested\/file1');// */

window.nested.file1 = true;
console.log('Imported nested/file1.js');
window.fileCounter++;

})();


window.fileCounter++;

})();


(function() {/*require('nested2\/*');// */

// Nested 2 -> File 1
console.log('Imported nested2/file1.js');
window.fileCounter++;

// Nested 2 -> File 2
console.log('Imported nested2/file2.js');
window.fileCounter++;

})();




(function() {/*require('importNestedNotExisting');// */

window.nested = {};
(function() {/*require('not-existing-file');// */

})();


window.fileCounter++;

})();


(function() {/*require('importNotExisting.js');// */

})();


(function() {/*require('importNotExisting');// */

})();



(function() {/*require('importedFileWithSubRequireNested\/file1');// */

window.importedFileWithSubRequireNested_file1 = true;
console.log('Imported importedFileWithSubRequireNested/file1.js');

(function() {/*require('importedFileWithSubRequireNested\/file2');// */

window.importedFileWithSubRequireNested_file2 = true;
console.log('Imported importedFileWithSubRequireNested/file2.js');
window.fileCounter++;

})();



(function() {/*require('importedFileWithSubRequireNested\/notFound');// */

})();


window.fileCounter++;

})();



(function() {/*require('nested-more-levels\/sublevel\/file1');// */

window.nested = {};
console.log('Imported nested-more-levels/sublevel/file1');
window.fileCounter++;

})();


(function() {/*require('nested-more-levels\/sublevel-file');// */

window.nested = {};
console.log('Imported nested-more-levels/sublevel-file');

(function() {/*require('nested-more-levels\/sublevel\/file2');// */

window.nested = {};
console.log('Imported nested-more-levels/sublevel/file2');
window.fileCounter++;

})();


window.fileCounter++;

})();



(function() {/*require('again\/importedFile');// */

})();


(function() {/*require('again\/*');// */

window.again = window.again || {}
if (window.again.importedFile) {
	throw "File imported twice";
}
window.again.importedFile = true;
window.fileCounter++;

})();




if (window.fileCounter != fileCounterExpected) {
	console.warn('Error: File counter not as expected: ' + window.fileCounter + "/" + fileCounterExpected);
}

console.log('Finished')