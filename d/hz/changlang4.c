// /u/beyond/hz/ changlang1.c ����
 
inherit ROOM;
void create()
{
        set("short","����");
        set("long", @LONG
���߽����ȣ�������������ȫ��һ�������ʲʻ�������������ԡ�ÿ
һ�������������������㶼�����ˣ���ԭ����·���Ҳ����ˡ�
LONG
        );
        set("exits", ([
            "south" : __FILE__,
            "east" : __FILE__,
            "north" : __FILE__,
            "west" : __DIR__"huanglongdong",
            
]));
        set("coor/x",60);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}
