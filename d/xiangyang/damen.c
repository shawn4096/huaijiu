// damen.c
// Modify By River 98/10
#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "����");
        set("long", @LONG
��������ݵĴ��ţ����Ⱥ�����Ĵ��ų����ţ��ſ������������һ���
�׽��ֵĴ��ҡ�������ݡ���̨��������������ʯʨ����Ӵ��ſ��ƽ�ȥ����
�������������������æµ�����ӡ��ſ�վ�������������������ϡ�
LONG
        );      
                 
        set("outdoors","���");
 
        set("no_fight", 1);
 
        set("exits", ([
               "south" : "/d/xiangyang/eroad1",
               "enter": "/d/wuguan/menlang",
        ]));
        
        set("objects", ([
                "/d/wuguan/npc/menwei" : 1,
        ]));

        set("coor/x",10);
 set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}


int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}
 
int valid_leave(object me,string dir)
{
     object *inv = deep_inventory(me);
     object *obj;          
     if( me->query_temp( "wg_help" ) || me->query_temp( "wg_road" ) == 2 )
          return notify_fail("�������˵����" + RANK_D->query_respect(me) +
                        "���������ĵ�һ��ɣ�˵�������Ͼ����������������\n");                      
     if( me->query_temp( "wg_juanzeng" ) )
          me->delete_temp( "wg_juanzeng" );
     if( me->query_temp( "wg_road" ) == 1 )
          me->delete_temp( "wg_road" );
     if( me->query("combat_exp") > 3000 && dir == "enter")
         return notify_fail("������ǰ����һ�죺����书�����ˣ������ѧ����ʲô�ˡ�\n");
//      if( !me->query("enter_wuguan") && dir == "enter")
//         return notify_fail("��������һ�죺���Ѿ��뿪����ˣ��Ͳ��ܽ�ȥ�ˡ�\n");
     obj = filter_array(inv,(:get_object:));
     if( sizeof(obj) && dir =="enter" )
         return notify_fail("��������ٺ�һЦ:���˭͵͵����ݰ���\n");
         return ::valid_leave(me, dir);
}
