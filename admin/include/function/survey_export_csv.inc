<?php

# $Id: survey_export_csv.inc,v 1.10.2.1 2003/04/22 23:51:27 jimmerman Exp $

// Written by James Flemer
// <jflemer@alum.rpi.edu>


// Start Y.Sakai 2004/05/21 15:04:00
function cnv_mbstr($str) {
	if (extension_loaded('mbstring')){
		return  mb_convert_encoding($str,$GLOBALS['ESPCONFIG']['enc_charset'],"auto");
	} else {
		return $str;
	}
}
function cnv_mbstr_csv($str) {
	if (extension_loaded('mbstring')){
		return  mb_convert_encoding($str,$GLOBALS['ESPCONFIG']['csv_charset'],"auto");
	} else {
		return $str;
	}
}// End Y.Sakai

/* {{{ proto array survey_generate_csv(int survey_id)
	Exports the results of a survey to an array.
	*/
function survey_generate_csv($sid) {
	$output = array();
	$columns = array(
            'RESPONSE',
            'SUBMITTED',
            'USERNAME',
        );
	$types = array(
            0,
            0,
            1,
        );
    $numcols = 3;
	$arr = array();

	$id_to_csv_map = array(
		'0',	// 0: unused
		'1',	// 1: bool -> boolean
		'1',	// 2: text -> string
		'1',	// 3: essay -> string
		'1',	// 4: radio -> string
		'1',	// 5: check -> string
		'1',	// 6: dropdn -> string
		'0',	// 7: rating -> number
		'0',	// 8: rate -> number
		'1',	// 9: date -> string
		'0' 	// 10: numeric -> number
	);

	$sql = "SELECT q.id, q.name, q.type_id
		FROM ".TABLE_QUESTION." q
		WHERE q.survey_id = $sid AND
		q.deleted = 'N' AND q.type_id < 50
		ORDER BY position";
	$result = mysql_query($sql);
	$numcols += mysql_num_rows($result);
	while( list( $qid, $col, $type ) = mysql_fetch_row($result) ) {
		if ($type == 8) {
			/* rate */
			$sql = "SELECT CONCAT(q.name, ' ', c.content)
			FROM ".TABLE_QUESTION." q, question_choice c
			WHERE q.id = $qid AND q.id = c.question_id";
			$result2 = mysql_query($sql);
			$numcols += mysql_num_rows($result2) - 1;
			while( list($col) = mysql_fetch_row($result2) ) {
				$str1 = $col;
				do {
					$str2 = $str1;
					$str1 = eregi_replace(
					"(^| )(what|which|why|how|who|where|how|is|are|were|the|a|it|of|do|you|your|please|enter)[ ?]",
					" ", $str2);
				} while ($str1 != $str2);
				$col = $str1;
				$col = trim(strtoupper(eregi_replace(
					"[^A-Z0-9]+", " ", $col)));
				$col = ereg_replace(' +','_',$col);
				array_push($columns,$col);
				array_push($types, $id_to_csv_map[$type]);
			}
			mysql_free_result($result2);
		} else {
			array_push($columns,$col);
			array_push($types, $id_to_csv_map[$type]);
		}
	}
	mysql_free_result($result);

	$num = 0;

	array_push($output, $columns);

	$sql = "SELECT r.id,r.submitted,r.username FROM ".TABLE_RESPONSE." r
		WHERE r.survey_id='$sid' AND r.complete='Y'
		ORDER BY r.submitted";
	$result = mysql_query($sql);
	while($row = mysql_fetch_row($result)) {
		// get the response
		$response = response_select_name($sid, $row[0]);

		$arr = array();
        array_push($arr, $row[0]);
        array_push($arr, $row[1]);
        array_push($arr, $row[2]);

		// merge it
		for($i = 3; $i < $numcols; $i++) {
			if (isset($response[$columns[$i]]) &&
					is_array($response[$columns[$i]]))
				$response[$columns[$i]] = join(',', $response[$columns[$i]]);
			switch ($types[$i]) {
			case 2: /* special */
				break;
			case 1: /* string */
				if (isset($response[$columns[$i]])) {
                    /* Excel seems to allow "\n" inside a quoted string, but
                     * "\r\n" is used as a record separator and so "\r" may
                     * not occur within a cell. So if one would like to preserve
                     * new-lines in a response, remove the "\n" from the
                     * regex below.
                     */
					$response[$columns[$i]] = ereg_replace("[\r\n\t]", ' ', $response[$columns[$i]]);
					$response[$columns[$i]] = ereg_replace('"', '""', $response[$columns[$i]]);
					$response[$columns[$i]] = '"'. cnv_mbstr_csv( $response[$columns[$i]]) .'"';
				}
				/* fall through */
			case 0: /* number */
				if (isset($response[$columns[$i]]))
					array_push($arr, $response[$columns[$i]]);
				else
					array_push($arr, '');
				break;
			}
		}
		array_push($output, $arr);
	}
	mysql_free_result($result);

	return $output;
}
/* }}} */

/* {{{ proto bool survey_export_csv(int survey_id, string filename)
	Exports the results of a survey to a CSV file.
	Returns true on success.
	*/
function survey_export_csv($sid, $filename) {
	$umask = umask(0077);
	$fh = fopen($filename, 'w');
	umask($umask);
	if(!$fh)
		return 0;

	$data = survey_generate_csv($sid);

	foreach ($data as $row) {
		fputs($fh, join(',', $row ) . "\n");
	}

	fflush($fh);
	fclose($fh);

	return 1;
}
/* }}} */
?>