MUDBĸ	MYC�P2 include/globals.h include/ansi.h include/combat.h $ kungfu/skill/huagu-mianzhang/bujue.c�  �q�       X   �������������  �           �  �  �  �            u   7      ?
 ? , b?m% � m% �� m �.� � 	�.�
A @_d �.� 
1% � 
1% � 
1 �.�A d �.�  �.�   �.� , �.� 2 �.�  �.b���q  !�  b?�� f5& �" ��" f5� �$D# �&%A �('�nf �*)D�d �&A �+d �+�� ,-��@A ,-��@A .B�c���E�de� /��q �+� �+� �(0�Ef �(1�nf ,-��@A ,-��@A ?�44 �" ��" f ,-��@C  ,-��@A �(0�nf �(1�Ef �2% �3B�c �$B�c# ./? /? ! �2 �('�Ef �4) /?
? 
1%W ?m%Q ?q m%G � %< �5 %2 �5 %( �� m% �  3% � 
11 6�q �2 �4) �2% �$C# /,-��@A ,-��@A �$B# .B��@;/ [��$	     �*^	  �  0�`	      ���q�J#	�#	Ȅ&	�#	��$	��նH%	�#	 �����#	��#	xz���#	d %	%	�#	��W�8�#	 ��4�#	Tg���$	8{#	4=��@�$	TPʶ��$	t����)	�>��M�����84	T�$	̶2	| %	�N0	$v#	p�'	�$	d�'	l�$	��$	h%	��$	�*^	�X�-%	�$	ذ$	��$	�%	d�#	��k���:�      feature/sserver.c$ kungfu/skill/huagu-mianzhang/bujue.c include/globals.h include/ansi.h include/combat.h is_character is_fighting �����಻����ֻ����ս��ʱ�ã�
 weapon
 query_temp �������ֲ����á����಻������
 huagu-mianzhang query_skill# ��Ļ������ƻ���������������ʹ�ã�
 strike query_skill_prepared query_skill_mapped parry+ ��û�м����������ƣ�����ʹ�á����಻������
 dulong-dafa' ��Ķ����󷨹������㣬���������಻����
 force+ ��û�м��������󷨣�����ʹ�á����಻������
 neili query% �������������㣬�����á����಻������
 jingli% �����ھ������㣬�����á����಻������
 jiali# �����̫���ˣ������á����಻������

 bujue_busy �Է��Ѿ����ˡ����಻������
� [1;33m
$N��Ȼ��һ������˫��һ������$n������ĳ���
[1;36m�ƺ����ֲ��أ����䲨��״���������˻�ǰ�ˣ�һ�˸߹�һ�ˣ����಻����
[0;0m /kungfu/skill/dulong-dafa force_effect
 combat_exp �����಻���� start_perform sld/pfm/bujue set_temp apply/defense add_temp
 no_perform apply_condition add /adm/daemons/combatd	 do_attack attackobz [0;36m
����$n���һ�������ۺ������������$N�������γɵ�������
���$Nֻ���ļ������������У����޷���ά�����ȵ����ơ�
[0;0m apply/attack apply/dodge delete_temp
 start_busy clear_condition is_ghostK [1;36m
$N����һ�٣���Ҳ֧�ֲ�ס�����ʱ�յ�������ֻ�ܻ����ջ����ƣ�
[0;0m perform attackob dohit��    �    O      y                                 "  #  %  &  (  )  +  ,  .  /  2  
3  4  5  6  
7  
8  9  :  
;  <  =  >  ?  @  
D  E  F  G  H  I  J  K  M  N  P  R  S  	T  U  V  ^  _  	`  a  
b  e  g  
g  h  
i  
j  k  l  m  	n  	o  	p  	q  r  v  w  
x  y    