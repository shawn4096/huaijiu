// Room: /d/jiaxing/yanyu.c

// by shang 97/6
inherit ROOM;

void create()
{
	set("short", "����¥");
	set("long", @LONG
����¥�����Ϻ����ĵ�һ��С���ϡ��Ϻ����겻�ϵ�ˮ������
���ֵ��������ɵġ�
LONG
	);

	set("exits", ([
                "north" : __DIR__ "nanhu1",
	]));

	set("coor/x",160);
  set("coor/y",-320);
   set("coor/z",0);
   setup();
}

