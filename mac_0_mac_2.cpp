void convo(

for(uint8_t yy = 0 ; yy < isize; yy++)
	     {
	 #pragma HLS PIPELINE
     for (uint8_t k = 0 ; k < wsize*wsize ; k++)
		{

    	 stream_convo_wgt >> wgt_mac_2[k];
    	 	// wgt_mac_2[k] = wgt_buff_0[0][k];;
		//wgt_mac_0[k]  = wgt_buff_0[ochan_no][k];
		}

	for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no++)
	  {
		#pragma HLS DEPENDENCE variable=linebuf inter WAR false

	   for(uint8_t xx = 0 ; xx < isize; xx++)
	     {
          #pragma HLS PIPELINE
		   if(xx == 0)
		   {
			    wgt_mac_0[0] = wgt_mac_2[0];
			    wgt_mac_0[1] = wgt_mac_2[1];
			    wgt_mac_0[2] = wgt_mac_2[2];
			    wgt_mac_0[3] = wgt_mac_2[3];
			    wgt_mac_0[4] = wgt_mac_2[4];
			    wgt_mac_0[5] = wgt_mac_2[5];
			    wgt_mac_0[6] = wgt_mac_2[6];
			    wgt_mac_0[7] = wgt_mac_2[7];
			    wgt_mac_0[8] = wgt_mac_2[8];
		   }
		   else if(ena_convo == 0)
		   {
			    wgt_mac_0[0] = 0;
			    wgt_mac_0[1] = 0;
			    wgt_mac_0[2] = 0;
			    wgt_mac_0[3] = 0;
			    wgt_mac_0[4] = 0;
			    wgt_mac_0[5] = 0;
			    wgt_mac_0[6] = 0;
			    wgt_mac_0[7] = 0;
			    wgt_mac_0[8] = 0;

		   }

		     if(wsize == 1)
		     {
			#pragma HLS PIPELINE
			//datatype_inh mcc = linebuf[rowAddr[0]][xx];
		    	stream_convo_out << wgt_mac_0[0]*linebuf[rowAddr[0]][xx];
		    	//std:: cout<<"wgt = "<< wgt_buff_0[ochan_no][0]*linebuf[rowAddr[0]][xx] << std::endl;
		    	//std:: cout<<"inp = "<< linebuf[rowAddr[0]][xx] << std::endl;
		     }
		     else
		     {
			#pragma HLS PIPELINE
			update_line_buff_0(linebuf, rowAddr, xx, isize,mac_buff);
 			stream_convo_out << mac_0_1(wgt_mac_0,mac_buff,ochan_no);

		     }

		   if(ochan_no == ochan_fac - 1)
		   {
		   if((yy) < (isize - 3 + padding))
					stream_convo_in >> linebuf[rowAddr[3]][xx];
		   else
					linebuf[rowAddr[3]][xx] = 0;
		   }

		   if(xx < wsize*wsize)
		   {
	        //for (uint8_t k = 0 ; k < wsize*wsize ; k++)
			//{
	        //wgt_mac_2[xx] = wgt_buff_0[ochan_no + 1][xx];;
			//wgt_mac_0[k]  = wgt_buff_0[ochan_no][k];
			//}
			   stream_convo_wgt >> wgt_mac_2[xx];

		   }

			if(ochan_no == ochan_fac-1 and xx == isize-1)
			{
				    if(rowena == 0){
					rowAddr[0] = 1 ; rowAddr[1] = 2 ; rowAddr[2] = 3 ; rowAddr[3] = 0 ;
					rowena = 1;}
					else if(rowena == 1){
					rowAddr[0] = 2 ; rowAddr[1] = 3 ; rowAddr[2] = 0 ; rowAddr[3] = 1 ;
					rowena = 2;}
					else if(rowena == 2){
					rowAddr[0] = 3 ; rowAddr[1] =  0; rowAddr[2] = 1 ; rowAddr[3] = 2 ;
					rowena = 3;}
					else if(rowena == 3){
					rowAddr[0] = 0 ; rowAddr[1] = 1; rowAddr[2] = 2 ; rowAddr[3] = 3 ;
					rowena = 0;}
			}
      }}}
