// Room: sroad1.c ���
// By jpei

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����һ������ʯ�̳ɵĴ�������߾����������񶼳ɶ��Ĵ������ˡ�����
������·��
LONG);
	set("outdoors", "�ɶ�");

	set("exits", ([
		"north" : __DIR__"dananmen",
		"southwest" : __DIR__"tulu3",
	]));

	set("coor/x",-150);
  set("coor/y",-70);
   set("coor/z",0);
   setup(); 
}
