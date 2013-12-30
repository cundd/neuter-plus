<?php
/**
 * Created by PhpStorm.
 * User: daniel
 * Date: 30/12/13
 * Time: 17:04
 */

namespace Cundd;


class FileParser {
	static protected $combineFilesRecursiveDepth = 0;

	protected $basePath = '';
	protected $wrapBefore = "(function() {";
	protected $wrapAfter = "})()";
	protected $separator = "\n\n";


	public function getRequiredFileIdentifiers($filePath) {
		$line          = '';
		$result        = array();
		$requiredFiles = array();;

		$filePath = $this->basePath . $filePath;


		$inputFile = @fopen($filePath, 'r');


		$pattern = "!^\\s*require\\(['\"]([^'\"]+)['\"]\\);!i";

		if ($inputFile) {
			while (($line = fgets($inputFile, 4096)) !== FALSE) {
				if (preg_match_all($pattern, $line, $result)) {
					$requiredFiles[$result[1][0]] = $result[0][0];
				}
			}

			fclose($inputFile);
		}
		return $requiredFiles;
	}

	public function combineFilesRecursive($rootFile) {
		$rootFilePath                 = $rootFile;
		$mergedSubRequiredFileContent = '';
		$requiredFileIdentifiers      = $this->getRequiredFileIdentifiers($rootFile);
		$rootFileContents             = '';

		if ($rootFilePath[0] != "/") {
			$rootFilePath = $this->basePath . $rootFilePath;
		}
		$rootFileContents = $this->getFileContents($rootFilePath);

		foreach ($requiredFileIdentifiers as $fileIdentifier => $fileIncludeCode) {
			$mergedSubRequiredFileContent = $this->separator;

			foreach ($this->resolveFileIdentifier($fileIdentifier) as $filePath) {
				++self::$combineFilesRecursiveDepth;
				$subRequiredFileContent = $this->combineFilesRecursive($filePath);
				--self::$combineFilesRecursiveDepth;

				$mergedSubRequiredFileContent = $mergedSubRequiredFileContent . $subRequiredFileContent . $this->separator;
			}

			$mergedSubRequiredFileContent =
				$this->wrapBefore
				. "/*" . StringUtility::findAndReplaceInString($fileIncludeCode, "/", "\\/") . "// */"
				. $mergedSubRequiredFileContent
				. $this->wrapAfter
				. $this->separator;

			$rootFileContents = StringUtility::findAndReplaceInString($rootFileContents, $fileIncludeCode, $mergedSubRequiredFileContent);

		}
		return $rootFileContents;
	}

	public function getFileContents($filePath) {
		return file_get_contents($filePath);
	}

	public function fileExists($filePath) {
		return file_exists($filePath);
	}

	public function resolveFileIdentifier($fileIdentifier) {
		$filePath  = $this->basePath . $fileIdentifier;
		$filePaths = array();

		if ($this->fileExists($filePath)) {
			$filePaths[] = $filePath;
			return $filePaths;
		}
		$filePath .= ".js";
		if ($this->fileExists($filePath)) {
			$filePaths[] = $filePath;
			return $filePaths;
		}
		if (strpos($fileIdentifier, '*') !== FALSE) {
			return $this->resolveFileIdentifierPattern($fileIdentifier);
		}

		return array();
	}

	public function resolveFileIdentifierPattern($fileIdentifier) {
		$filePaths      = array();
		$relativePath   = '';
		$basePathLength = strlen($this->basePath);
		return glob(($this->basePath . $fileIdentifier . ".js"));
	}

	public function setBasePath($newBasePath) {
		if (strlen($newBasePath) > 0 && substr($newBasePath, -1) != "/") {
			$newBasePath .= "/";
		}
		$this->basePath = $newBasePath;
	}

	public function setWrapBefore($newWrap) {
		$this->wrapBefore = $newWrap;
	}

	public function setWrapAfter($newWrap) {
		$this->wrapAfter = $newWrap;
	}

	public function setSeparator($newSeparator) {
		$this->separator = $newSeparator;
	}
}