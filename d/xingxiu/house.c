inherit ROOM;
void create()
{
        set("short", "������Ժ");
        set("long", @LONG
��������Ǵ������ͥԺ������ά������˳Ʋ���Ϊ�������ſڴ�����
����Ͷ��Ժ������˾��ú����졣���߾�����������ġ�
LONG);
        set("exits", ([ 
              "west" : __DIR__"yili2",
        ]));
        set("objects", ([
                __DIR__"npc/hkid": 1,
                __DIR__"npc/bayi": 1, 
        ]));
        set("outdoors", "�����");
        set("coor/x",-290);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-290);
 set("coor/y",160);
   set("coor/z",0);
   setup();
}
