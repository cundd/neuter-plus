<?php
//
//  main.cpp
//  neuter-plus
//
//  Created by Daniel Corn on 27/12/13.
//  Copyright (c) 2013 cundd. All rights reserved.
//

use Cundd\FileParser;

require_once __DIR__ . '/FileParser.php';
require_once __DIR__ . '/StringUtility.php';

function main($argc, $argv) {
	$useStandardOut   = FALSE;
	$inputFilePath    = "";
	$outputFilePath   = "";
	$combinedContents = "";
	$fileParser       = new FileParser();
	$outputFile       = "";

	for ($i = 1; $i < $argc; $i++) { /* We will iterate over argv[] to get the parameters stored inside.
	* Note that we're starting on 1 because we don't need to know the
	* path of the program, which is stored in argv[0] */
		if ($i + 1 != $argc) { // Check that we haven't finished parsing already
			if ((string)($argv[$i]) == "--input") {
				// We know the next argument *should* be the filename:
				$inputFilePath = (string)($argv[$i + 1]);
			} else if ((string)($argv[$i]) == "--output") {
				$outputFilePath = (string)($argv[$i + 1]);
			} else if ((string)($argv[$i]) == "--basePath") {
				$fileParser->setBasePath((string)($argv[$i + 1]));
			} else if ((string)($argv[$i]) == "--wrapBefore") {
				$fileParser->setWrapBefore((string)($argv[$i + 1]));
			} else if ((string)($argv[$i]) == "--wrapAfter") {
				$fileParser->setWrapAfter((string)($argv[$i + 1]));
			} else if ((string)($argv[$i]) == "--separator") {
				$fileParser->setSeparator((string)($argv[$i + 1]));
			} else if ((string)($argv[$i]) == "--stdout") {
				$useStandardOut = TRUE;
			} else {
				echo "Not enough or invalid arguments" . PHP_EOL;
				exit(1);
			}
		}
		$i++;
	}

	if ($inputFilePath == "") {
		echo "Please specify the input file path ('--input')" . PHP_EOL;
		exit(1);
	}
	if ($outputFilePath == "") {
		echo "Please specify the output file path ('--output')" . PHP_EOL;
		exit(1);
	}


	echo "Try to read from file '" . $inputFilePath . "'\n";
	try {
		$combinedContents = $fileParser->combineFilesRecursive($inputFilePath);

		if ($useStandardOut) {
			echo $combinedContents;
		} else {
			file_put_contents($outputFilePath, $combinedContents);
		}
	} catch (Exception $e) {
		echo $e;
	}
	return 0;
}


main($argc, $argv);
