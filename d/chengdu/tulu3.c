// Room: tulu3.c ��·
// By jpei

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�����������С·����Ϊ�Ĵ��Թž��Ǹ���֮�أ����Է�����ȥ��
���ܵ��������������ࡣ�����Ǵ��У�����ʮ���ﴦ�����������񶼳ɶ��ˡ�
LONG);
	set("outdoors", "����");

	set("exits", ([
//		"east" : __DIR__"wroad2",
		"northeast" : __DIR__"sroad1",
		"southwest" : __DIR__"tulu2",
	]));

	set("coor/x",-160);
  set("coor/y",-80);
   set("coor/z",0);
   setup(); 
}
