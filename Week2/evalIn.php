#! /bin/php
#dnasjnhd
<?php
/* This function is used to assign values to variables
 and doing some strange operations */

function outputme($_x, $_y) {
	echo "( $_x, $_y )<br>";
}

$x = 5;
$y = 3;

outputme($x, $y);
$x += 2 * $y;
outputme($x, $y);
$x += ($y *= 2);
outputme($x, $y);

?>