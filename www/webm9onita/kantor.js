var jmlRekHome = 11;
var timeRefresh = 5000;	// 5 detik

var defJmlRekHome  = 21;
var defTimeRefresh = 6000;
var tlCookies = 365;		// 1 thn.

var arIdEq = "";
var id_Eq = 0;
var id_Gr = 0;
var arHome = [];

var toH, toW, toM;
var bulan = ["Jan","Feb","Mar","Apr","Mei","Jun","Jul","Agt","Sep","Okt","Nov","Des"];
var months  = new Array("Januari", "Febuari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember");
var calDays = new Array("Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu");

dojo.require("dojo.collections.Store");
dojo.require("dojo.charting.Chart");
dojo.require("dojo.html.display");
dojo.require("dojo.widget.*");

var isiHomeReq		= getXmlHttpRequestObject();
var isiMesinReq		= getXmlHttpRequestObject();
var isiGroupReq		= getXmlHttpRequestObject();

function getXmlHttpRequestObject() {
	if (window.XMLHttpRequest) {
		return new XMLHttpRequest();
		//return XMLHttpRequest();
	} else if(window.ActiveXObject) {
		return new ActiveXObject("Microsoft.XMLHTTP");
		//return ActiveXObject("Microsoft.XMLHTTP");
	} else {
		document.getElementById('p_status').innerHTML = 'Status: Tidak bisa membuat objek XmlHttpRequest.  Segera upgrade browser Anda.';
	}
}

function tahuIsiHome(isi) {	// isi data pengukuran terbaru
	var str;

	arIdEq = isi;
	stopTimer();
	//document.getElementById("gedebug").innerHTML += " xisi : " + isi;
	if (isiHomeReq.readyState == 4 || isiHomeReq.readyState == 0) {
		//document.getElementById('tombol').innerHTML = "blabla";
		str = "getData.php?fetchMenu=1";
		str+= "&arIdEq="+arIdEq;
		isiHomeReq.open("GET", str, true);
		isiHomeReq.onreadystatechange = handleReceiveDataHome; 
		isiHomeReq.send(null);
	} else {
		//alert("gak bisa");
	}
}

function handleReceiveDataHome() {
	var jmlDaya = 0;
	var ketika = "";
	var arData = [];
	var obj = {};
	
	if (isiHomeReq.readyState == 4) {
		var xmldoc = isiHomeReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//document.getElementById("gedebug").innerHTML += "<br>handle data : " + arIdEq;
		//alert("Jml : " + n_messages);
		for (var i = 0; i < n_messages; i++) {
			var nama   = message_nodes[i].getElementsByTagName("nama");
			var nilai  = message_nodes[i].getElementsByTagName("nilai");
			var titik  = message_nodes[i].getElementsByTagName("titik");
			var waktu  = message_nodes[i].getElementsByTagName("waktu");
			var saiki  = message_nodes[i].getElementsByTagName("saiki");

			var idtitik = titik[0].firstChild.nodeValue;
			var besar	= parseInt(nilai[0].firstChild.nodeValue);
			ketika 		= waktu[0].firstChild.nodeValue;
			document.getElementById("nilai"+idtitik).innerHTML = besar;
			document.getElementById("nilaiG"+idtitik).innerHTML = besar;
			document.getElementById("waktu"+idtitik).innerHTML = ketika;
			document.getElementById("waktuG"+idtitik).innerHTML = ketika;
			//document.getElementById("waktu"+i).innerHTML = saiki[0].firstChild.nodeValue;
			jmlDaya += besar;
			obj = {no: i, titik: idtitik, nilai: besar, waktu: ketika};
			arData.push(obj);
		}
		document.getElementById("totalDaya").innerHTML = jmlDaya;
		document.getElementById("totalUpdate").innerHTML = ketika;
		updateDataHome(arData);
	}
	//toH = setTimeout("tahuIsiHome()",defTimeRefresh); //Refresh our chat in 2 seconds
	//document.getElementById("gedebug").innerHTML = " jml Data isi : "+;
	toH = setTimeout('tahuIsiHome("'+arIdEq+'")',defTimeRefresh); //Refresh our chat in 2 seconds
}

function updateDataHome(isi) {
	//document.getElementById("gedebug").innerHTML  = "<br>jml isi : "+isi.length;
	//document.getElementById("gedebug").innerHTML += "<br>jml n   : "+n.length;
	//document.getElementById("gedebug").innerHTML += "<br>jml arH : "+arHome[1].length;
	//var str = "";
	for (var h=0; h<isi.length; h++) {
//		str = isi[h].nilai + ",";
//		document.getElementById("gedebug").innerHTML += "<br>isi"+(h+1)+" : "+str;
		arHome[h].shift();
		arHome[h].push(isi[h]);
		for (var u=0; u<arHome[h].length; u++) {
			arHome[h][u].no = u;
		}
		grafikKWz(arHome[h], "grafik"+n[h], 8000, 0, "", 1, 15, 10, " (x"+(tf/1000)+" detik yg lalu)")
	}
}

function resetArData() {
	for (var i=0; i<n.length; i++) {
		var deret = [];
		for (var j=0; j<rek; j++) {
			//isi = (i*10+j);
			obj = {no: j, titik:"999", nilai:0, waktu:"0"};
			//obj = (i*10)+j;
			deret.push(obj);
			//document.getElementById('tahuIsi').innerHTML  += deret[j].nilai + " ";
		}
		arHome.push(deret);
	}
}

function tahuIsiMesin(idEq) {	// isi data pengukuran terbaru
	var str;
	id_Eq = idEq;
	stopTimer();
	if (isiMesinReq.readyState == 4 || isiMesinReq.readyState == 0) {
		str  = "getData.php?fetchMenu=2&idEq=" + idEq;
		//document.getElementById("gedebug").innerHTML = str;
		isiMesinReq.open("GET", str, true);
		isiMesinReq.onreadystatechange = handleReceiveDataMesin; 
		isiMesinReq.send(null);
	} else {
		//alert("gak bisa");
	}
}

function handleReceiveDataMesin() {
	if (isiMesinReq.readyState == 4) {
		var xmldoc = isiMesinReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//document.getElementById("gedebug").innerHTML += " " + id_Eq;
		for (var i = 0; i < n_messages; i++) {
			var nama   = message_nodes[i].getElementsByTagName("nama");
			var nilai  = message_nodes[i].getElementsByTagName("nilai");
			var titik  = message_nodes[i].getElementsByTagName("titik");
			var waktu  = message_nodes[i].getElementsByTagName("waktu");
			var saiki  = message_nodes[i].getElementsByTagName("saiki");

			var idtitik = titik[0].firstChild.nodeValue;
			document.getElementById("nilaiM"+idtitik).innerHTML = desimal(nilai[0].firstChild.nodeValue, AP);
			document.getElementById("waktuM"+idtitik).innerHTML = waktu[0].firstChild.nodeValue;
			
			
		}
	}
	toM = setTimeout("tahuIsiMesin("+id_Eq+")",defTimeRefresh); //Refresh our chat in 2 seconds
}

function tahuIsiGroup(idGr) {	// isi data pengukuran terbaru
	var str;
	id_Gr = idGr;
	stopTimer();
	if (isiGroupReq.readyState == 4 || isiGroupReq.readyState == 0) {
		str  = "getData.php?fetchMenu=2&idGr=" + idGr;
		//document.getElementById("gedebug").innerHTML = str;
		isiGroupReq.open("GET", str, true);
		isiGroupReq.onreadystatechange = handleReceiveDataGroup; 
		isiGroupReq.send(null);
	} else {
		//alert("gak bisa");
	}
}

function handleReceiveDataGroup() {
	var arData = [];
	var obj = {};
	
	if (isiGroupReq.readyState == 4) {
		var xmldoc = isiGroupReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//document.getElementById("gedebug").innerHTML += " " + id_Eq;
		for (var i = 0; i < n_messages; i++) {
			var nama   = message_nodes[i].getElementsByTagName("nama");
			var nilai  = message_nodes[i].getElementsByTagName("nilai");
			var titik  = message_nodes[i].getElementsByTagName("titik");
			var waktu  = message_nodes[i].getElementsByTagName("waktu");
			var saiki  = message_nodes[i].getElementsByTagName("saiki");

			var idtitik = titik[0].firstChild.nodeValue;
			var besar	= desimal(nilai[0].firstChild.nodeValue, AP);
			var ketika	= waktu[0].firstChild.nodeValue;
			document.getElementById("nilaiGp"+idtitik).innerHTML = besar;
			document.getElementById("waktuGp"+idtitik).innerHTML = ketika;
		
			obj = {no: i, titik: idtitik, nilai: besar, waktu: ketika};
			arData.push(obj);
		}
		updateDataHome(arData);
	}
	toM = setTimeout("tahuIsiGroup("+id_Gr+")",defTimeRefresh); //Refresh our chat in 2 seconds
}

function defaultSetting() {
	//if (status == 1) {
		//document.getElementById("timeRefresh").value = (defTimeRefresh/1000);
		document.getElementById("timeRefresh").value = defTimeRefresh/1000 + " detik";
		document.getElementById("jmlRekHome").value = defJmlRekHome + " data";
	//} else alert("ga muncul");
}

function ubahSetting() {
	var n = document.getElementById("jmlRekHome").value;
	var t = document.getElementById("timeRefresh").value;
	var ket = document.getElementById("ketSetting");
	var lokTimeRefresh, lokJmlRekHome, lokIdDept;
	
	ket.innerHTML = "";
	
	for (var i=0; i < document.formDept.dept.length; i++) {
		if (document.formDept.dept[i].checked) {
			lokIdDept = document.formDept.dept[i].value;
		} 
	}
	
	lokIdDept = parseInt(lokIdDept);
	//alert("nilai lokIdDept : " + lokIdDept);
	
	if (isNaN(lokIdDept)) {
		alert("Anda belum memilih Departemen. Silakan memilih.");
		return 0;
	} 
	
	//alert(isNaN(t));	//if (isNaN(parseInt(t))) alert("no num");
	if (t == "" || isNaN(parseInt(t))) {
		document.getElementById("timeRefresh").value = defTimeRefresh/1000 + " detik";
		ket.innerHTML = "Nilai periode diisi konfisi default = " + (parseInt(defTimeRefresh)/1000) + " detik<br>";
		lokTimeRefresh = defTimeRefresh;
	} 
	else	lokTimeRefresh = parseInt(t)*1000;

	if (n == "" || isNaN(parseInt(n))) {
		document.getElementById("jmlRekHome").value = defJmlRekHome + " data";
		ket.innerHTML += "Jumlah Rekaman Home diisi konfisi default = " + defJmlRekHome + " data<br>";
		lokJmlRekHome = defJmlRekHome;
	} 
	else 	lokJmlRekHome = parseInt(n);

	ket.innerHTML += "Konfigurasi berhasil diubah dan disimpan<br>";
	setCookie("timeRefresh", lokTimeRefresh, tlCookies);
	setCookie("jmlRekHome", lokJmlRekHome, tlCookies);
	
	setCookie('id_dept', lokIdDept, tlCookies);
	//alert("Setting konfigurasi:<br>Periode : "+(parseInt(defTimeRefresh)/1000)+" detik<br>Jumlah rekaman : "+lokJmlRekHomex);
	//setCookie("jmlTitik", jmlTitik, tlCookies);
	window.location.href = "home.php";
}

function setStyle(x){
	document.getElementById(x).style.background="yellow";
}

function unsetStyle(x) {
	document.getElementById(x).style.background="white";
}

function setCookie(c_name,value,expiredays) {
	var exdate = new Date();
	exdate.setDate(exdate.getDate()+expiredays);
	document.cookie = c_name + "=" +escape(value)+((expiredays==null) ? "" : "; expires="+exdate.toGMTString());
}

function getCookie(c_name) {
	if (document.cookie.length>0) {
		c_start=document.cookie.indexOf(c_name + "=");
		if (c_start != -1) {
			c_start = c_start + c_name.length+1;
			c_end = document.cookie.indexOf(";",c_start);
			if (c_end == -1) c_end=document.cookie.length;
			return unescape(document.cookie.substring(c_start,c_end));
		}
	}
	return "";
}

function setCookiesDefault() {
	setCookie('jmlRekHome', jmlRekHome, tlCookies);
	setCookie('jmlTitik', jmlTitik, tlCookies);
	setCookie('timeRefresh', timeRefresh, tlCookies);
	setCookie('id_dept', id_dept, tlCookies);
	setCookie('usr', "operator", 1);
	setCookie('pwd', "opr", 1);

}

function cekCookies() {
	//stopTimer();
	//masukCek();
	var last_login = getCookie('last_login');
	if (last_login!=null && last_login!="") {
		jmlRekHome  = getCookie('jmlRekHome');
		timeRefresh = getCookie('timeRefresh');
		var xlastLogin = getCookie('last_login');
		var setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		//alert("last Login : " + xlastLogin);
	} else {
		setCookiesDefault();
	}
	
	var d = new Date();
	var tgl = d.getDate() + " " + bulan[d.getMonth()] + " " + d.getFullYear();
	//alert(tgl);
	//exdate.setDate(exdate.getDate());
	setCookie('last_login', tgl, 1);	
}

function startup() {
	jmlRekHome = 11;
	timeRefresh = 5000;	// 5 detik
	//alert ("kantorskript dijalankan");
	//id_dept = getCookie('id_dept');
	//defTimeRefresh = getCookie('timeRefresh');
	//alert("nilai id_dept : " + id_dept + "  time : " + defTimeRefresh);
	mongsoSaiki();
	resetArData();
	//tahuIsiHome("blabla");
	//tahuIsiMesin();
}

function stopTimer() {
//	clearTimeout(toW);
	//alert("mati timer");
	clearTimeout(toM);
	clearTimeout(toH);
}

function mongsoSaiki() {
	toW = setTimeout( "mongsoSaiki()", 1000 );
	var t    = new Date();
	var dino = t.getDay();
	var tgl  = t.getDate();
	var bln  = t.getMonth();		// januari = 0
	var thn  = t.getFullYear();
	var jam  = t.getHours();
	var mnt  = t.getMinutes();
	var dtk  = t.getSeconds();
	//document.getElementById('mongso').innerHTML = "testing waktu javascript";
	document.getElementById('mongso').innerHTML = calDays[dino] + ", " + tgl + " " + months[bln] + " " + thn + " " + jam + ":" + t0(mnt) + ":" + t0(dtk);
}

function t0(data) {		// tambahkan nol di depan format waktu jika hanya 1 digit
	if (data < 10) {
		return ("0" + data);
	} else {
		return data;
	}
}

function arEq(isi) {
	var strId = "";
	var nArIdEq = arIdEq.length;
	//*
	for (var k=0; k<nArIdEq; k++) {
		if (k==(nArIdEq-1))
			strId += arIdEq[k];
		else 
			strId += arIdEq[k] + "_";
	}
	//*/
	//arIdEq = strId;
	//document.getElementById('gedebug').innerHTML = "Hasil : " + nArIdEq + ", " + isi;
	
	return strId;
}

function testing() {
	document.getElementById('gedebug').innerHTML += "gedebug : ";
}

var printArray = function (x, idx) {
   document.writeln('['+idx+'] = '+x);
}
