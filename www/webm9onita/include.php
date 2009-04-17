
<?php 
	require("config.php");
	require("header.php");
	require_once("database.php");
	
	// ambil semua cookies yang tersimpan
	if ($_COOKIE["id_dept"]) {
		$c_id_dept = $_COOKIE["id_dept"];
	}
	
	if ($_COOKIE["jmlRekHome"]) {
		$rek = $_COOKIE["jmlRekHome"];
	}
	
	if ($_COOKIE["timeRefresh"]) {
		$tf = $_COOKIE["timeRefresh"];
	}
	
	/*/
	if (!$_COOKIE["id_dept"]) {
		$c_id_dept = 0;
	} else $c_id_dept = $_COOKIE["id_dept"];
	if (!$_COOKIE["jmlRekHome"]) {
		$rek = 11;
	} else $rek = $_COOKIE["jmlRekHome"];
	if ($_COOKIE["timeRefresh"]) {
		$tf = 5000;
	} else $tf = $_COOKIE["timeRefresh"];
	//*/
?>
