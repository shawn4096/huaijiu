MUDBĸ	MYC�P! include/globals.h include/ansi.h  kungfu/skill/huifeng-jian/mie.cp  4�`�       X   ,	>�	>�����H  l  x  x  x  d  d  d  p            �   ;        b� b?
 ? , b?m% � m% �� m �.?�m% �	 
1 �.�A x �.�
  �.�A x �.�  �.�	 � �.�	 � �.�	 � �.�  �.? � ��� �d �A fb�q � @_�  @V   b? �  � �Fq �!�" Fq ?|��	# ��	# fD�$ � �&%� �&'� �(A )�q �&*�n �&+�n �&'�n �($A �,C�c �d �.A- /�Bf���p @]�&%� �&'� �(A 0�q �&*�n �&+�n �&'�n �.A- �d /����?  @`�(� 12���  ��  12���  * 3��q �4B �d �.A- .��� 5�q �&%� �&'� �(A �A (fb�,�Bf?�fc �.C- ?  @`�(� 12���  ��  12���  6�Df���.7�./?�* �&*� �&+� �&'� � b? �&
 � ! �&%�n �&'�n �8 ?�& ? � ?  @V @V�(� ? �& ?�&
 ��  9��q  ? � :�q /?� � b? �&
 � ! �&%�n �&'�n �8 ?�& ? � ?  @V @V�(� ? �& ?�&
 ��  9��q  ? � :�q /p8Q	 �  <�W	     �il	 U  bu4�`��L	�M	�UN	�M	��L	X]M	�q�4YN	��L	@M	䔬�8�L	pM	�y��JN	pX��,CM	,硷d?M	�����`N	��p�<@N	�^����M	x�x���u	��¶�N	H8��r	XKr	�ь��N	��M	#f	(�^	��M	dvN	��L	w�0�M	 _O	�N	��r	`GN	p8Q	���WN	��S	\���#N	����il	�%��l�M	���P�'��^�      feature/sserver.c kungfu/skill/huifeng-jian/mie.c include/globals.h include/ansi.h weapon
 query_temp is_character is_fighting ��ֻ�ܶ�ս���еĶ���ʹ�á�

 skill_type query sword% �������޽����������á��𽣡��ķ�����
 huifeng-jian query_skill+ ��ط��������Ϊ����������δ�����𽣡���
 query_skill_mapped �����ڲ���ʹ�á��𽣡��ķ���
 linji-zhuang1 ����ڹ���Ϊ���δ����ʩչ���𽣡�ֻ���˼�������
 force! �����õ��ڹ��롸�𽣡��ķ���㣣�
	 max_neili+ ���������Ϊ���㣬����������ʩչ���𽣡���
 neili' �����������������������ʩչ���𽣡���
 jingli# ��ľ������ޣ�������ʩչ���𽣡���
 huifeng/mie ������ʹ�á��𽣡��ķ���
 addj [1;37m$NƮ������ʹ�����Ҿ������𽣡��ķ�����ʱ�������Ʈ�ݶ�������ǧ�������裬����ͷ����������
[0;0m pfm-target/huifeng-mie pfmer = %O
 victim temp dbase  = %O
 query_entire_temp_dbase
 combat_exp huifeng-mie apply/sword add_temp apply/attack set_temp, [1;37m$N�ۻ����ң������˸����ֲ�����
[0;0m apply/dodge apply/parry add_busy �� start_perform remove_effect2 [1;37m$N���Ѽӱ���������Ըй���ƵƵ�մ졣
[0;0m /adm/daemons/combatd	 do_attack $N�ۼ��ֿ죬ʶ����$n��һ�У�

 start_busy $N�����˸����ֲ������������ˣ�
 finish_mie2 ���������á��𽣡��ķ���
 delete_temp4 [1;33m

$N������Ӧ��$n�Ľ�·������������ˡ�
[0;0m> [1;33m

$N�˹���ϣ����ܷ�����Ľ����ƺ�Ҳ������ʧ�ˡ�
[0;0m remove_effect perform finish_mie2kk    �    O  �  �   
�   �                     
                                 !  $  	%  &  '  (  *  ,  -  /  1  3  
7  
8  
9  	:  ;  <  =  
>  ?  @  
A  B  F  
G  
H  
I  	J  K  L  M  
N  O  P  R  
S  T  U  V  
Z  	[  \  ]  a  	c  
d  
e  
f  g  h  
i  j  
k  l  m  n  o  r  y  
{  
|  
}  
~  �  �  �  	�  �  �  	�  �  
�  �  �  �  
�  �  
�  �  �  �  	�  �  �  	�  �  
�  �  �  �  
�    