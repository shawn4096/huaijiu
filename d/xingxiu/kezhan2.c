
inherit ROOM;

void create()
{
        set("short", "��ջ��¥");
        set("long", @LONG
���������������ջ�Ķ�¥��¥���������ڣ���ʱƮ����һ��������
��Ŀ�����ζ����������˿����ڴ������������˯һ����
LONG);
        set("sleep_room", "1");
        set("no_fight", "1");

        set("exits", ([ 
             "down" : __DIR__"kezhan",
        ]));

     
        set("coor/x",-310);
  set("coor/y",170);
   set("coor/z",10);
   set("coor/x",-310);
 set("coor/y",170);
   set("coor/z",10);
   setup();
}
