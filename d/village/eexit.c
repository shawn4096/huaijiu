// Room: /d/village/eexit.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�����ǻ�ɽ���£�����������ɽ��·�ˡ�������һ��С��ׯ���������˼�
�����࣬�����ǹ����ճ������������Ϣ���������
LONG
	);

	set("exits", ([
	"west" : __DIR__"shilu6",
	"east" : "/d/huashan/path1",
]));
	
        set("no_clean_up", 0);
        set("outdoors", "��ɽ");

        set("coor/x",30);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

