// Room: damen.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ߵ�һ����լ��Ժ���ſڣ����Ž��գ��ſ�վ�ż����Ҷ���һ�������ص��ǣ�
һ��Ҫ�����鷳�����ӡ���ǰ����������ʯʨ�ӣ����弶��ʯ̨���������ȶ���ͭ
���Ĵ��š����ó������ǵ��ش����ס����
LONG
        );
         

        set("objects", ([
                __DIR__"npc/jiading":2,
        ]));
        
        set("exits", ([
                "south": __DIR__"shide",
                "north": __DIR__"xiaoxiang1",
        ]) );

        set("coor/x",-10);
 set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

