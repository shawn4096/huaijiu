MUDBĸ	MYC�P! include/globals.h include/ansi.h  d/wudang/npc/attecker.c�
  DEk	  6    X   ��p�l�p������  T  �  �  �  �
  �
  �
  �
          -�   v 3   C2|�C2GbC+|�C+Gb C,|�C,GbC.|�C.GbC/|�C/GbC-|�C-GbC0|�C0GbC1|�C1Gb�: ,� ;<,� =h�c,� >?,� @ N,� AB,� C2,� D,� E,� F,� G�,� H�,� IX,� JX,� K
,� L,� M,� ^,� N,� O,� P,� /^,� Q,� R,� 0^,� S,� T,� U,� 1^,� �^,� �^,� �^,� �^,� �^,� �^,� OP,� /�,� R?,� QM,� S,� 0�,� T?,� 1�,� U?,� NM,� NM,� ,+ V?c,0W X,0Y /- C  
q	 Z,�  /y@ _�& ? ,( [<[A�/? m%	 ? 
m /? ]\  ^<^@�/
_a` cbccc q q /b? 
 ?d ? ae b?]f b? gR (�
cdb�^ b?h@? a@ fe ?0 ?ai b?j? b?k�� ?k�� ?kO? ?kN? ?kR? ?kQ? ?k?jR ? ?k� ?kP? ?kM? ?hG? aG fe ?hH? aH fe ?hJ? aJ fe ?hK?gO f ?l ?hm? am fe ?hn? an fe ?hI? aJ fe ?ho? aG fe p? ae c�q<qA��?hr? ae  ./? /? m% ? 
?
1
 ?d ?s  qA��.7 ?t? ae   ?^?  qA��.
 ?d ./u�? ,: ./- 6 	
 D+a

 D,a D-a  D.a!" D/a#$%&'()*+,- D0a./012/30 D1a456789 D2a/til�L	  �  ��L	      $�M	   w  ,ZN	    `XO	  
  yQ	  J  �V	 �  �M	     %%%%%��������)���������*���������%��ဘ�%)���������*���������9�����%��ဘ�%)���%%������%*�����%����������)���������*���������������)���8�������%��*�����%%%%��������)���������*���������%����)���������*���������%����)���������%%*�����������%��)���������*�����%%%��������)���������*�����%��������)���������*�����%7�:�DEk	�L	�M	��L	�L	��L	�IM	P=M	�L	x�L	��L	��L	L<M	JM	8�L	$*M	�>M	�M	�)M	�L	x6M	�L	��L	��L	4;M	�?M	��L	*M	�=M	��L	��L	�(M	�L	�IM	��L	��L	��L	�=M	��L	�2M	��L	H�L	P�L	XBM	GM	D�L	��N	@M	d	M	t/M	,eM	��Q	T]i	H]	��o	��c	��t	8�N	x�c	<�L	 �L	M	�N	�����M	x4N	�N	(N	|"N	��M	�M	xcN	�_N	<@N	�`N	��M	`N	��L	\KM	d?M	��L	�,M	l2M	�M	P6M	�(M	|b	�N	i	̃N	D�L	yQ	�h	�M	 XN	`�g	(�L	��L	����DM	$�M	��L	�UN	pM	0�M	4YN	�JN	�N	X\N	�XM	��M	��M	\OU	l�L	(IU	X]M	HM	t2[	�p	<o	@n	��n	(+U	��q	\�S	T�T	EEEEEEEE�>m�      inherit/char/npc.c d/wudang/npc/attecker.c include/globals.h include/ansi.h
 taiji-jian	 damo-jian	 fumo-jian jinshe-jianfa qingmang-jian yuxiao-jian yunu-jianfa songshan-jian murong-jianfa huashan-jianfa duanjia-jianfa huifeng-jian liangyi-jian quanzhen-jianfa	 cibei-dao fanliangyi-dao liuhe-daofa murong-daofa wenjia-daofa shandian-daofa
 xiuluo-dao xuanxu-daofa yanxing-daofa wuchang-zhang fengmo-zhang tianshan-zhang
 xinyuegong
 weituo-chu zui-gun
 weituo-gun piaomiao-bianfa qingxu-bian shuishangpiao suibo-zhuliu yanling-shenfa yufeng-xiang tianlong-xiang yunu-shenfa zhaixingshu
 xiaoyaoyou zhongyuefeng huashan-shenfa	 tiyunzong chui sword blade whip gun	 gangzhang ����� ������ ������ �ڵ����� ɽ�� �ݿ� attacker gender ���� age long1 ��һ�һ�������ɷ��ģ����ʱ��ʱ����а�����Ц��

 combat_exp attitude peaceful str int con dex max_qi max_jing neili	 max_neili jiali location	 taizuquan cuff force taiji-shengong parry dodge hammer club staff /clone/weapon/ wield /clone/armor/yexing-yi wear	 startroom greeting wd_job1
 query_temp kill_ob [1;31m
ֻ�� name query ת����������Ͳ����ˡ�
 [0;0m
 unconcious id weapon query_skill set
 skill_type query_skill_mapped	 set_skill reincarnate eff_jing jingli qi stare  checking victim is_fighting
 is_killing say ������������ sword_skill blade_skill staff_skill
 club_skill
 whip_skill dodge_skill weapon_list
 first_name checking create
 unconcious init accept_fight greeting do_copy #global_init#pp    �    O  �  	
  	  	  	  	  	  	  	    	    	  
  	  	  	  	  	  
  
  
   
!  	"  #  	$  	%  	&  	'  	(  	)  	*  	+  	,  	-  	.  	/  	0  	1  	2  	3  	4  	5  	6  	7  	8  	9  	:  	;  	<  	=  	>  	?  	@  	A  B  C  D  K  L  M  O  P  V  W  Y  Z   b  c  k  m  n  o  q  r  s  t  u  v  w  x  z  {  |  }  ~    �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  �  
�  �  �  
�  �  �  �  
�  �   �   �   �   �   
�           