#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
           set("short","��������");
           set("long",@long
����һ��ƻ�ͨ���Ĵ����̣�һ����������������ǽ�߷���������
���¯���յ������������������庺�����ͻ�����ּ�Ǯ�������ǽ��
��һ���Ѿ�����Ĵ�����(sign)��
long ); 

        set("objects",([
           __DIR__"npc/xue" : 1,
        ]));
          
        set("exits",([
           "south" : __DIR__"yili2",
        ]));                                                    
  
        set("item_desc",([
         "sign" : "�����ʽ���ȡ��շ������ƽ�
                 �� make <��ɫ> <����>  �����졣
                 ���� : make $HIR$ ɨ����\n"
           ]));

        set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",170);
   set("coor/z",0);
   setup();
}
