// Room: /d/village/miaoyu.c

inherit ROOM;

void create()
{
        set("short", "��̳��");
	set("long", @LONG
����һ��ʮ���ƾɵ�С�����﹩������������̳�������Ѿ��ܲ���
�ˣ�����Ҳ���˺ܶ೾�����������кܾ�û������������ˡ���Ŵ���
ƶ����̫�ã��Ѳ��ټ�������콵���������ˡ�
LONG
        );
        set("exits", ([
	"north" : __DIR__"shilu5",
]));
        set("objects", ([
                __DIR__"npc/wupo": 1 ]) );

        set("no_clean_up", 0);

        set("coor/x",-20);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
