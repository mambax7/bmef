<?php

# $Id: espcross.inc,v 1.1 2003/02/22 05:21:20 jimmerman Exp $

// Written by Kon Angelopoulos
// <angekproductions@iprimus.com.au>

/* {{{ proto void mkcrossformat (array weights, integer qid)
   Builds HTML to allow for cross tabulation/analysis reporting.
 */
function mkcrossformat($counts, $qid, $tid) {
    $cids = array();
    $cidCount = 0;

    // let's grab the cid values for each of the questions
    // that we allow cross analysis on.
    if ($tid == 1) {
        $cids = array('Y', 'N');
    } else {
        $sql = "SELECT id FROM ".TABLE_QUESTION_CHOICE."
                WHERE question_id = $qid
                ORDER BY id";
        $result = mysql_query($sql);
        while ($cid = mysql_fetch_row($result)) {
            array_push($cids, $cid[0]);
        }
        mysql_free_result($result);
    }

    $bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];

?>
<table width="90%" border="0">
<tbody>
<?php

    while(list($content,$num) = each($counts)) {
        if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
            $bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
        else
            $bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];

        if ($cidCount >= count($cids))
            $cidCount = count($cids) - 1;

?>
<tr bgcolor="<?php echo $bg; ?>">
<td width="34" height="23" align="left" valign="top" bgcolor="#0099FF">
  <div align="center">
    <input type="checkbox" name="cids[]" value="<?php echo $cids[$cidCount++]; ?>" />
  </div>
</td>
<td width="506" align="left"><?php echo $content; ?></td>
</tr>
<?php
    }
?>
</tbody></table>
<?php
}
/* }}} */
?>