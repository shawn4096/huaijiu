// Room: /d/huashan/canglong.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
��ɽ�������յ��Ǳ��壬����֮����͵����ǲ����롣�����Լ��
�ף����һ�ף�����ɽ֮·������ɽ��֮�ϣ����༹�¹⻬ͦ�Σ�����������
�䣬���������������һʯ��(shibei)��
    ��������������ɽ��·����������������ɽ�ķ��·�������ǻ�ɽ���մ�
֮һ�������������¡���
LONG
	);

	set("exits", ([ /* sizeof() == 3 */
		"southdown" : __DIR__"zhenyue",
		"westup" : __DIR__"sheshen",
		"northdown" : __DIR__"husun",
	]));

	set("objects", ([ 
		__DIR__"npc/monkey" : 1,
	]));

	set("item_desc", ([
		"shibei" :
"ʯ�����ż������֣�������֮Ͷ�鴦������˵���꺫�����ϴ���֮����\n"
"Ҳ��������������ΪҪ����ɽ�ϣ�����ɽ��д��Ͷ�������ͼ��˾��𡣺�\n"
"�����ǻ����ص��ع�������ɽ�����Ӱ������ŵ������ġ�\n"
	])) ;

	set("no_clean_up", 0);
	set("outdoors", "��ɽ" );

	set("coor/x",70);
  set("coor/y",50);
   set("coor/z",60);
   setup();
}
