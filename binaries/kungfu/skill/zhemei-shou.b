MUDBĸ	MYC�P include/globals.h  kungfu/skill/zhemei-shou.c4  ��X�  
     X   ���������    <  <  <    $  (  4            N  	 8    �0% �0.�	0.�
A �D aC P� C d2 dh .C x2 d� .C �2 dd�
 .C �2 x� .�& .�|�CGB�  x�Be�c ./� %
 �  �.� 2 �.�   �.�!h �" ./�# � $�.�%A d &�../'�c.C P�C d2& � 5% �*(B�c�)( c �" .C x2& � 25A �
A b�Bf?�cb�!+D�c?e �,+�Bf �"2 .C �2&% � 25& �- ��- f5! �.�
A f �"2 .C �2&0 � 25&" � & �- ��- f5 � /� �"2 .C �5& � d5& �0 1N �
A fb�21� �23� �24� �"d �50A 6J�./?  /�
A fb�21�n �23�n �24�n �70 ./ Da/�YN	     �qN	  (  |�N	      P�N	 W  `�P	  �   @�P	     $�P	  Q  �U}	 �  �M	   @  �h	��X��L	Xᴷ�a��ϥ���?���`�L	�,M	|5M	��L	pM	4SN	8GϷ��M	T�P	l2M	d?M	$@�P���T~N	�N	�;�������UN	�M	 �N	<�|	��M	��L	xp\�<@N	�U%���M	�N	�`N	XJQ	�o	 �]�������N	�N	�N	��M	bN	��M	#N	��L	�v~	dvN	��M	��P	0�M	��L	�U}	l�M	<�W	��V	E04��      inherit/skill/skill.c kungfu/skill/zhemei-shou.c include/globals.hL $N��������һָͻ�����ںϽ�����ָ�����壬�ṹ�Ͻ������ƺ�ΰ��ָָ������$nT $N���������������������Ե���������������ݺᣬ�������У���·�����븫���ϳ�һ·����$nN $N˫���Եý������أ�ʹ��ʱԽ��Խ��ɬ�������趯һ�����ȣ�����Խ��Խ�أ�����ֹ��H $Nʮָ̽�������ֻ�����������Ʈ���л�ȥ��$n��������ȴ�̺������ҵķ�����ʽT $N˫�������˦�������������޹ǣ��鶯֮������һ�ƣ���һ�����Ƶ�$n����һ����Ҳ�������� hand parry liuyang-zhang zhemei-shou query_skill actionb $N����һ�䣬������������֮����������Ϣ����$n�ġ�����Ѩ����������ȭ�ͻ�����������$n�ؿڵġ�����Ѩ�� damage_type ���� dodge force< $N��������һ��������һ���ھ��������м���������һǰһ�����$nd $N����ת�˸�СȦ���ȿ���׼����ֻ��ָ����$n���󣬴�Ĵָ��Сָ���ű㼴��£����ס$n���ţ�$n��ʱ�������� damage ����N $N˫����ץ��ʹ������ɽ��÷�֡��ĸ����书��ץ�д��ۣ����м��ƣ�����$n�����Ŵ�Ѩ� ��ʱ$N����������������ң�����ַ��ӵ����쾡�£������������ۣ���������
Ȼ����ң����ѧ��������������Ȼ��Ȼ��Ҳʹ�˳�������ʹ�����������տ̶�
$N�������գ��Թ���$nҪ����ֱ����$n���òҿ��ޱ� weapon
 query_temp secondary_weapon ����ɽ��÷�ֱ�����֡�
 jingli query ���������������ɽ��÷�֡�
 neili ���������������ɽ��÷�֡�
 receive_damage add	 max_neili �������������
 weiwo-duzun! ��İ˻�����Ψ�Ҷ��𹦻��̫ǳ��
 /kungfu/skill/zhemei-shou/ cold_poison query_condition apply_condition qi receive_wound
 combat_exp
 start_busy move	 marks/add apply/attack add_temp apply/defense apply/dodge set_temp
 reset_temp delete_temp lvl_temp
 action_msg query_action valid_learn valid_enable hit_ob practice_skill valid_combine perform_action_file
 reset_temp #global_init#dd    �  �  �   �   �   �   �   �   �   �   �   �   �   �   �   �   	�   �   �                
                !  #  #  $  %  )  +  ,  -  .  /  3  4  6  7  ;  <  =  @  A  E  F  G  I  
J  
K  
L  M  
N  O  Z  [  \  ]  ^  _  �     