/******************************************************************************************
  cb_nome => Callback

  vi_nome => variables int
  vc_nome => variables char/string
  vf_nome => variables float
  vd_nome => variables double
  vp_nome => variables file

  return -1 => error
  return 0  => ok
******************************************************************************************/
#include <iostream>
#include <bitset>
#include <cmath>

#include "hex2int.h"

using namespace std;

/******************************************************************************************
 FUNCTION CB_OPEN_HEX2INT
******************************************************************************************/
int hex2int(char *vc_bitsvalue) {
    bitset<8>	_bitset0, _bitset1;
    float		vf_valor = 0;

    _bitset0 = vc_bitsvalue[1];
    _bitset1 = vc_bitsvalue[0];
	
	vf_valor += (_bitset0[0]*pow(2,float(0)));
	vf_valor += (_bitset0[1]*pow(2,float(1)));
	vf_valor += (_bitset0[2]*pow(2,float(2)));
	vf_valor += (_bitset0[3]*pow(2,float(3)));
	vf_valor += (_bitset0[4]*pow(2,float(4)));
	vf_valor += (_bitset0[5]*pow(2,float(5)));
	vf_valor += (_bitset0[6]*pow(2,float(6)));
	vf_valor += (_bitset0[7]*pow(2,float(7)));
	vf_valor += (_bitset1[0]*pow(2,float(8)));
	vf_valor += (_bitset1[1]*pow(2,float(9)));
	vf_valor += (_bitset1[2]*pow(2,float(10)));
	vf_valor += (_bitset1[3]*pow(2,float(11)));
	vf_valor += (_bitset1[4]*pow(2,float(12)));
	vf_valor += (_bitset1[5]*pow(2,float(13)));
	vf_valor += (_bitset1[6]*pow(2,float(14)));
	vf_valor += (_bitset1[7]*pow(2,float(15)));
	
	return (int) vf_valor;
}
