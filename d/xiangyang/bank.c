// Room: /xiangyang/bank.c
// Looklove y2k/4/09

inherit ROOM;

void create()
{
        set("short", "����ի");
        set("long", @LONG
����һ�����ֺŵ�Ǯׯ�����м��������ʷ����ȫ�����ض��зֵꡣ����
�е���Ʊ�����ǳ��ã�ͨ��ȫ����
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaoxiang1",
        ]));

        set("objects", ([
                __DIR__"npc/banker" : 1,
          
        ]));
 
        setup();
}
