// Room: eroad3.c ���
// By jpei

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����һ������ʯ�̳ɵĴ�������ϱ�ͨ���Ĵ����в������治Զ�����Ǵ�
������ĵط��ˡ�
LONG);
	set("outdoors", "�ɶ�");

	set("exits", ([
		"east" : __DIR__"eroad4",
		"southwest" : __DIR__"eroad2",
	]));

	set("coor/x",-70);
  set("coor/y",-10);
   set("coor/z",0);
   setup(); 
}
