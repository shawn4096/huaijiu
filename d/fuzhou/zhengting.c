// Room: /d/fuzhou/zhengting.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǹ����ھֵ���������ֻ̫ʦ��һ���ſ�����������������ͷ���ֳ�
�̴������ڱ�Ŀ��˼��ǽ�Ϲ��ż����ֻ���һ�ѱ�����
LONG
	);

	set("exits", ([
		"north" : __DIR__"biaoju",
	]));

    set("no_fight",1);
	set("objects", ([
        __DIR__"hubiao/linzhennan" : 1,
	]));

	set("coor/x",90);
  set("coor/y",-490);
   set("coor/z",0);
   setup();
}

