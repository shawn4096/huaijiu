// by xiaoyao

inherit ROOM;
void create()
{
        set("short","�ּ��");
        set("long",@LONG
������һ���ּ�С���������������ѡ�������Ǹ��ݳǵ�����
���ţ������Ͽɴ����Ϲ㶫��
LONG);
        set("objects", ([
           __DIR__"obj/hua3": 1,
        ]));
        set("outdoors", "��ɽ");
        set("exits",([ /* sizeof() == 1 */
              "north"      : "/d/fuzhou/bridge",
            "southwest" : __DIR__"road13",
        ]));
        set("coor/x",100);
  set("coor/y",-500);
   set("coor/z",0);
   setup();
}


