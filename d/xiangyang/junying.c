inherit ROOM;

void create()
{
        set("short", "�ɹž�Ӫ");
        set("long", @LONG
�������ɹŹ�����������ʱ��Ӫ��ʱʱ��ʿ������Ѳ�ߡ�
�����ϱ��ܵ���������
LONG
        );
        set("outdoors", "����");
        set("objects", ([
                "/d/xiangyang/npc/weishi" : 3,
        ]));


        set("exits", ([
                "southwest" : __DIR__"outnroad2",
                "enter" : __DIR__"yingzhang",
        ]));

        set("coor/x",30);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}
