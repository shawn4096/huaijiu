// Room: /d/village/tiejiangpu.c

inherit ROOM;

void create()
{
        set("short", "������");
	set("long", @LONG
����һ�����Ǽ�ª�������̣����������Ǹ������裬����ú��������
ǽ�Ϲ��ż�����ͷ�����ӵĽ�������ż����Ƴ�ͷ����������ǽ���ż���
�³�¯��������
LONG
        );
        set("exits", ([
	"west" : __DIR__"shilu2",
]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/feng": 1 ]) );

        set("coor/x",10);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
 
