<?php
	require("include.php");
	//global $c_id_dept;		$c_id_dept= $_GET['id'];
	//global $c_time_refresh;	$c_time_refresh = $_GET['tf'];		//echo "t ref   : " . $c_time_refresh ."<br>";
	//global $c_jml_rek_home;	$c_jml_rek_home = $_GET['rek'];		//echo "jml rek : " . $c_jml_rek_home ."<br>";
	require("menu.php");
	//echo $iki;

	if (!$rek) {
		$rek = $_GET['rek'];
		//echo "rek : ".$rek;
	}
	
	if (!$tf) {
		$tf = $_GET['tf'];
		//echo "tf : ".$tf;
	}
?>

<div id="page">
<div id="tahuIsi">

<h2 class="title"><strong>Konfigurasi</strong></h2>
<table id="tabelIsiSetting" border="0" bordercolor="black" cellpadding="1" cellspacing="0" width="500">
	<tr><td width="200">Periode pengambilan data</td>
	<td>: <input type=text id="timeRefresh" size=41 value="<?php echo ($tf/1000) . " detik" ?>" title="Periode pengambilan data" onfocus="setStyle(this.id)" onblur="unsetStyle(this.id)" > </td></tr>
	<tr><td><br>Jumlah data yang ditampilkan </td>
	<td><br>: <input type=text id="jmlRekHome"  size=41 value="<?php echo $rek . " data" ?> " title="Jumlah data yang tampil" onfocus="setStyle(this.id)" onblur="unsetStyle(this.id)" > </td></tr>
</table>
<br>
<?php
	require("dept.php");		// buat menampilkan daftar perusahaan & departemen
?>

<span id="tombolSetting">
	<button id="btnDefault" type="button" onClick="defaultSetting()">Default</button>	
</span>
</div>	<!-- akhir div dept-->
<div id="ketSetting"><br></div>


</div> <!--   tahuIsi -->

<div id="sidebar"></div> 
	<!-- end div sidebar -->

	<div style="clear: both;">&nbsp;</div>
</div> <!--   page -->

<?php
	require("footer.php");
?>
