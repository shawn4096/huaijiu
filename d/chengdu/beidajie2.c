// Room: /d/chengdu/beidajie2.c
// By Jpei

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
���ǳɶ��ı���֡�����ͨ�򱱳��ţ��ϱ��Եúܷ�æ��
LONG
	);
        set("outdoors", "�ɶ�");

	set("exits", ([
		"north" : __DIR__"beidajie3",
		"south" : __DIR__"beidajie1",
	]));

	set("coor/x",-150);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

