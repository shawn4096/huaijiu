MUDBĸ	MYC�P2 include/globals.h include/ansi.h include/combat.h   kungfu/skill/weituo-chu/chaodu.c�  H
6�       X   �Go�dGo�����  ,  T  T  T  �  �  �  �            �   N     ?m&	 � 
 ? , b?m% � m% �� m �.� @_�m% �
	 1 �.�  �.�
  �.�  �.�A , �.� � d2 �.�
 �A 
fc2 �.�A � �.�A , �.� A , !�.�"   #�.�" 1% �"$ 1 %�.�
& � '�.�
( �2 )�.�
* �2 +�.,�- c.c/c�- c0c1c��q �2�
 �4-�
- 3c �5 �46@ �47@ � �A cb� fb�A f�
cb��eb�9�
8   �Befb�9�
8   �Befb? � :�Fq ;<�A b;<�$B b�=  @]�
>  @\@\@]�?A ��c�?| ? @(� ? @*�� ?BA? ?CA�Bf D��q ;E? ? F�c ? H�cG I�Bef? T J��q ? @($� ? @*�� ? H�cG ? F�c I�Bef? ./?  /? K ? Lq /Mq .t"��$	     ��$	  �  hHI	  �  %%H
6�J#	�#	Ȅ&	��$	�#	���H%	�#	H�$	8{#	�#	 *W���a	h�&��Y%	��2��5	�Nc�xy#	��#	d����$	��$	� 
�X�$	4�#	`�h��#	����H�#	,U��r#	X�2�%	\��#	C��X�$	�Ё���$	��@�$	T���`�^�d~#	D�#	 |��-ŷ|�#	�#	<E	��$	, %	H�%	��%	0�#	p9	��V	h%	d7'	@ %	��V	$v#	��$	�$	�$	%	0�g�$�'	��$	 �P	| %	hHI	|�i�ذ$	 ��t�j�\�ѷ     ��x�    feature/dbase.c feature/sserver.c  kungfu/skill/weituo-chu/chaodu.c include/globals.h include/ansi.h include/combat.h is_fighting is_character% �����ȼ��֡�ֻ�ܶ�ս���еĶ���ʹ�á�
 weapon
 query_temp
 skill_type query club% �������޹����������á����ȼ��֡�����
	 sl_chaodu5 �����ȼ��֡��������ܼ���̫��������Υ��ͣ����ɶ��ã�
 menggu' �����ַ��Ű��࣬����ܹ����÷����񹦡�

 sl_leidongK ������ʹ��Τ���Ƶġ��׶����졹��ȫ�������Ѿ���ע�����б����У���Ͼ�����ˡ�

 weituo-chu query_skill1 �㡸Τ���ơ���Ϊ����������δ�����򡸳��ȼ��֡���
	 query_str apply/strength# ��������������޷��ó������ȼ��֡�
 con force/ ��ĸ��ǲ������޷����ܡ����ȼ��֡��Ľ�մ�����
 buddhism+ ��������Ϊ����������δ�����򡸳��ȼ��֡���
 jingang-quan< �����ȼ��֡����Խ�մ����������޼᲻�ݣ�����ȭ��Ϊ��ǳ��?

 yijin-jing) ����ڹ���Ϊ���δ����ʩչֻ���˼�������
 query_skill_mapped% �����õ��ڹ��롸���ȼ��֡��ķ���㣣�
 parry% �������޷�ʹ�á����ȼ��֡����й�����
	 max_neili/ ���������Ϊ���㣬����������ʩչ�����ȼ��֡���
 neili+ �����������������������ʩչ�����ȼ��֡���
 jingli' ��ľ������ޣ�������ʩչ�����ȼ��֡���
R [0;34m
ͻȻ$N��¶��⣺�����ȼ��֡������α��ǣ���ͬΤ����������һ�㣬��ȭͻ������ name  [0;34m���У����塱��һ���� ����ķ�����ǧ�����Ƿ���$n��
 [0;0m move ����Ƭ set unequip value weapon_prop id	 is_killer damage = %d
 /adm/daemons/combatd skill_power is_busy real_yjj set_temp add qi receive_damage receive_woundT [1;33m
$n���������ô���ͰԵ�����ʽ,�мܲ�������ȭ�����У��߹ǵ����������ѣ�
[0;0m report_status
 start_busy �����ȼ��֡� start_perform remove_effect2W [1;33m
$n�ۼ�$N�����׺ݣ������мܣ��������ػ��У����������ɣ������������һ����
[0;0m delete_tempC [1;32m
�㾭��һ��ʱ���������ԣ��ֿ�����ʹ�á����ȼ��֡��ˡ�
[0;0m ���ȼ���
       �Ƿ����񹦣�����Τ���ơ������⹥���������б������飬����ǧ��Ƭ��Ƭ�������֡�
       ���ǡ�Τ���ơ����ռ���ʽ��
 perform help remove_effect2��    �    O      �  	                                   !  #  $  &  '  )  *  ,  -  /  0  2  3  4  6  7  9  :  <  =  &?  @  A  B  
C  
D  E  F  G  H  I  
J  K  
L  M  N  O  P  
Q  R  S  U  V  W  
Y  Z  \  ]  ^  _  `  
a  b  c  d  g  h  i  j  k  l  s  
t  
u  	�    