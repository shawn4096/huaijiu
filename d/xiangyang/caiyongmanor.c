// /d/xiangyang/caiyongmanor.c

inherit ROOM;

void create()
{
	set("short", "����ׯ");
	set("long", @LONG
������ǰ���Ǻ�ĩ���˲������ӵ�ׯԺ����Ů���ļ��������ڴˡ��ܲپ�
��ʱ���ݷù��������¹���Ǩ���������Ƕ��˷��ˡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"south" : __DIR__"lantian",
		"north" : __DIR__"caiyongtomb",
	]));

	set("coor/x",-10);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}

