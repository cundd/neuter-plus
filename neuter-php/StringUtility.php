<?php
/**
 * Created by PhpStorm.
 * User: daniel
 * Date: 30/12/13
 * Time: 17:32
 */

namespace Cundd;


class StringUtility {
	static public function findAndReplaceInString($input, $search, $replace) {
		if (!$input) {
			return "";
		}
		return str_replace($search, $replace, $input);
	}
}
