MUDBĸ	MYC�P! include/globals.h include/ansi.h  d/hj/npc/supu.cL	  ��}	  6    X   �kJ��kJ������  @  �  �  �  8	  <	  @	  L	          -�   _ ,    ,� 	
,� U,� ,� ,� A,� 	p ,� �,� `,� T,� X,� T,� X,� X,� �,� �,� ^,� h,� h,� h,�  !"#$p:%p:&'() ,� ,+ *C,� +,- ,� ,0. /,00 ,0/y21  3�.y24  5�.) 678@y c9c:cyq y<;A ./b�>= �> 3%' �>? �>= 3% �> �> 3 @��q /�2; 6 A��q B<BA��? C; ? C4 . //�> b�> b? D  BA��.?
 .�>? de?f22AE��q 
�� Fq b?�F C+|�C+Gb?G? �<1A H�>I c�>J cKc��q .?�&	 ?L M ?q C+|�C+Gb?G? �<1A H�>I c�>J cKc��q .?G? �<1A H�>I c�>J cKc��q . C+|�C+Gb?G? �<1A H�>I c�>J cKc��q .�>? de?f2- M��q N��q ?GO P?q ../? m%	 ? 

1 /?� /�� Q�.?�# R�>S c�T�U?  V�.�>J W X�>S c�Y�/Z�>S c�[��<4A \A�./?  /? � ]@�^ Gc�	 ? q /- 6  D+a/? l�L	 �  ��L	       `XO	 k  dbO	  �  t�Q	     <tR	  Y  �M	     %%%%%��������)���������*���������%��ဘ�%)���������*�������������%��ဘ�%)���%%������%*�����%����������)���������*���������������)���������%��*�����%%%%��������)���������*���������%����)���������*���������%����)���������%%*�����������%��)���������*�����%%%��������)���������*�����%��������)���������*�����%7�8�����}	�L	�M	�Z	�$a	XWo	��l	��O	�Iq	<�L	 �L	M	�N	���x4N	�BO	��L	��M	�M	(N	|"N	��M	�M	xcN	�_N	<@N	�`N	�	M	d	M	�,M	l2M	t^O	ĳO	��T��O	���<t	80v	l�_	�����O	�zx��YO	$ZO	Y�0Y¶�N	ܘm	̃N	��|	�M	<q#�`�s	��$J���fM	�M	X���DM	��w	��L	�SN	��L	��M	����,N��l�L	l�M	X]M	���8m	��L	��u	 IN	(�L	`N	�V	����X���|	4\z	p�t	hIO	��L	�m� XN	4l\	|�b	��Q	H�{	�!Y	8��<tR	`	`JN	�5`	E82 ��      inherit/char/npc.c d/hj/npc/supu.c include/globals.h include/ansi.h /d/hj/obj/yangpi /clone/weapon/wandao /clone/weapon/bishou /d/hj/obj/jiunang ���� supu gender ���� age long5 һ������Ĺ�����������, �����˵�һ��ʿ��³�˵Ķ��ӡ�
 attitude heroism unique
 combat_exp shen str int con dex max_qi max_jing neili	 max_neili unarmed blade parry dodge inquiry ����/ �������ҵ������ˣ���ÿ��ɱ��Ұ�Ƕ���������Ƥ��
 ������b ���ĸ質����������ˣ�����˵���������񳪵û��á�
���⼸��������һֱû���������裬һֱû�ڼ�������
 ˤ�� ���� ��үү9 ���Ǽ����˰����������������ҵ����ƣ���ҽţ����ƥ�ļ�����
 ��³��) �����Ұ������ǹ�������ĵ�һ��ʿ��������
 chat_chance chat_msg3 �����Ժ����µ�: ��ҲҪѧ�Ұ�����Ϊ�����˵�һ��ʿ��
5 ������������: ���Ķ�ȥŪһ���ϵȵ���Ƥ���͸�������? 
 wield /clone/armor/yangao wear
 supu_fight
 query_temp say ���ǲ��Ǳ��Թ����� supu_accept say ��ƾʲô���ұ����أ�K [0;36m$N����$nһ�ۣ��ò�̫��׼�ĺ���˵��������δ���Ĳ�ԭ��һ��ʿ����λ���� /adm/daemons/rankd query_respect ��ͺ����д�(fight)���°ɣ�
 [0;0m supu1 set_temp eff_qi query qi6 [0;36m$N��$n˵���һ�û����Ϣ�ã����һ����ɡ�
[0;0m> [0;36m$N��$n˵���ðɣ����Ҿ�ͬ���д꼸�аɣ��㵽Ϊֹ��
[0;0m checking delete_temp is_fightingL [0;36m$N��$n��ס����̾�����Ǻ��˹�Ȼ��һ�㣬�ҷ����ˣ�����һЩ���
[0;0m /d/hj/obj/shoujuan move
 $N����$nһ unit name ��
 violate_unique< [0;36m$N����$nһƲ�죬˵�������Ǻ��˵���ѧ������ˡ�
[0;0m' $N��$n���˸��񣬴�ͷɥ�����뿪�����

 /d/hj/road $N��ͷɥ�����߻�����
 ��û�����������
 ?  id$ say ���⺺��ǿ�������˴������ʲô�� kill_ob ��⣬�����ˣ�
 ����Ƥ smile  say лл������ ah O say ��ɱ���˴���ǣ�������Ҳ�Ǹ���ʿ��Ҫ��Ҫ����[1;33m����[0;36mһ�£�
[0;0m
 destroying drop  parse_command_id_list goods checking create accept_fight accept_object ask_me
 destroying #global_init#    �    O  �  �   	�   	�   	�   	�   	�   �   
�   	   	  	  	  
  
  
  
  	  		  	
  	          	          "  #  &  	'  +  ,  4  5  6  7  8  ;  <  =  >  
?  @  
J  
K  
L  M  P  Q  R  S  T  U  V  
W  
X  $Y  \  ]  ^  
_  
`  $a  
d  
e  'f  i  
j  
k  $l  o  p  q  
r  s  {  |  }  ~    �  
�  �  �  �  �  �  �  
�  �  �  �  �  �   �     