MUDBĸ	MYC�P� include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h include/net/daemons.h include/net/daemons.h include/net/services.h & adm/daemons/network/services/gwizmsg.c�   /c�       X   �r>�`r>������  �  �  �  �  �  �  �  �            J   6     �/ym% zm% z�0% z�0m /	
 b	 b�b�b?�b?|b� ��G	  	  �� ��G?Gb	?	�m% ��G?G�m% ��G?GGhm O 	�G�G	 cc	 cc?cc?cc?cc? c?  cc $� /zm% z�0% z�0 /�G(�G	  /	 �G b?m% !�G|m% 	"�G m #$�G�G /�G�G� %�G !�G&c�Gcc'�Gcb !�G&c�Gc(c'�Gcb	+)*B��G?F 	�G�G,	 c-c?c.c�Gcc //�G� 01!�G�GF,
  02/�G!�G�GF,
 354'�G%�G /"d�#	       `�$	    ��$	   %%�� /c�J#	�$	��$	`�$	�$	��$	�y#	��#	t�ѷD�$	\�$	��$	�v#	<M'	(�$	0�#	L|#	D�$	��$	��$	�9*	hs#	��$	�}F	�@	�K	p�N	�I	��$	��$	��$	��$	d0	,�$	�ӷ��$	�]3	�IR	�JJ	��$	lD	x;3	��$	�8	h�R	��L	��+	h�#	�D	�kB	p�#	ܫ$	|#	�S�     \�ѷ     feature/clean_up.c feature/dbase.c& adm/daemons/network/services/gwizmsg.c include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h include/net/services.h Root yuj /adm/daemons/network/dns_master
 query_muds	 query_svc |   @@@ query_mud_name   . gwizmsg HOSTADDRESS PORTUDP @@@gwizmsg||NAME:
 ||PORTUDP: query_udp_port
 ||WIZNAME: ||CNAME: ||GWIZ:
 ||CHANNEL:	 ||EMOTE:1 @@@
 send_udp NAME query_mud_info WIZNAME dns_mudp$ /adm/daemons/network/services/ping_q send_ping_q EMOTE @ GWIZ :  dns_fake Gwiz: %s %s
%s aux_log @@@warning||NAME: ||MSG: Fake gwiz msg:  ||FAKEHOST: CNAME
 channel_id %s@%s	 %s(%s@%s) /adm/daemons/channeld sj
 do_channel create send_msg incoming_request..$    �                    5          a  �  �  �  	�  	�  
�  
�  �  �  &�  
�  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  
�  �  �  �  �  �  �  �  �  �  �  �  �  	�  �  �  �    