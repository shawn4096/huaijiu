// /d/jiaxing/dating.c ����
// by shang 97/6

inherit ROOM;

void create()
{
        set("short", "����");
	set("long", @LONG
���ڹ�ɫ����, ���Ϸ������Ŷ���ǽ���Ϲ������ֻ���
Ȼǽ��һ�մ��оŸ�Ѫ��ӡ, ׯ��½�����������У�����Ѫ
��ӡ��������
LONG
	);

	set("exits", ([
                "south" : __DIR__"houyuan",
                "out" : __DIR__"tianjing",
	]));

        set("objects", ([
                 __DIR__"npc/lu-liding" : 1,
        ]));
	set("coor/x",150);
  set("coor/y",-340);
   set("coor/z",20);
   setup();
}

