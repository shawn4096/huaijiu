inherit ROOM;

void create()
{
        set("short", "Ӫ����");
        set("long", @LONG
�������ɹŹ�����������ʱ��Ӫ��Ӫ���������󽫡�ıʿ
������ȥ��������̸�ۡ���ִ��
LONG
        );
        set("outdoors", "����");
        set("objects", ([
//         "/d/xiangyang/npc/mengge" : 1,
                "/d/xiangyang/npc/weishi" : 3,
        ]));


        set("exits", ([
                "out" : __DIR__"junying",
        ]));

        set("no_fight",1);

        set("coor/x",30);
  set("coor/y",30);
   set("coor/z",10);
   setup();
}
