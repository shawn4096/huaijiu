// Room: xiaohe.c
// Looklove y2k/4/26

inherit ROOM;

void create()
{
        set("short","С��");
        set("long", @LONG
һ������������С�ӣ����ϼ��Ÿ���ľ�ţ����������ϣ����·���֨֨��
������Զ���м�����Ƥ��С�����ںӱ���Ϸ���Ŷ�����һ�Һܴ��լԺ������
����һ�����Ĵ��š��ϱ���������
LONG
        );

        set("exits", ([
                "south" : __DIR__"liuzz",
                  "north" : __DIR__"xue_men",
        ]));
 
        set("coor/x",-40);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

