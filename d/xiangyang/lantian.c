// /d/xiangyang/lantian.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Թų������񣬲������ʺã�Ҳ������ҩ���������ǳ�������������
����ȥ��������·��
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"southeast" : __DIR__"shanxiroad2",
		"north" : __DIR__"caiyongmanor",
	]));

	set("coor/x",-10);
  set("coor/y",60);
   set("coor/z",0);
   setup();
}

