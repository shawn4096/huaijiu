// Room: /d/shaolin/shijie1.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "ʯ��");
	set("long", @LONG
��������ɽ��´������ɽɽ�š�һ��������ʯ����ͬ���������Ѷ��ϣ�
ֱû�ƶˡ���ɽȺ���������ɫ��ɽ�����˸����������С֮�⡣�����м�
��������С���������ƺ�������������Щʲô��
LONG
	);

	set("exits", ([
		"east" : __DIR__"ruzhou",
		"west" : __DIR__"xiaojing1",
		"northup" : __DIR__"shijie2",
	]));

//	set("objects",([
//		__DIR__"npc/xiao-fan" : 1,
//		__DIR__"npc/tiao-fu" : 2,
//	]));

	set("outdoors", "shaolin");
	set("coor/x",90);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",90);
 set("coor/y",110);
   set("coor/z",0);
   setup();
}
/*
int valid_leave(object me, string dir)
{
	if (dir == "northup" && !wizardp(me))
		return notify_fail("��ɽ��Ϊɽ·������������ʱ��ɽ��\n");
	return 1;
}
*/
