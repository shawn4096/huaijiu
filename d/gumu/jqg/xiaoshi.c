// xiaoshi.c

inherit ROOM;
#include <ansi.h>

void create()
{
       set("short",HIC"С��"NOR);
       set("long", @LONG
��ٲ�����һ��С�ң�ֻ������������������������һ�Ѳ������֮
��������м������Ƶ���޺�һ����ľ���Ƶĵ��ӡ�
LONG
        );
       set("exits", ([
	  "west" : __DIR__"zhongtang",
	  "east" : __DIR__"dashi",
       ]));	

       set("objects", ([
               CLASS_D("gumu") + "/yang" : 1,
       ]));
       setup();
}

void init()
{
        object me=this_player();
        mapping fam = me->query("family");
        if( fam && fam["family_name"] =="��Ĺ��" 
         && fam["generation"] == 3 && fam["master_name"]){
           me->set("family/generation", 4);
           me->set("class","sworder");
           tell_object(me,HIG"ϵͳ����ѱ����Զ�ת������ˡ�\n"NOR);
           }
        if( fam && fam["family_name"] =="��Ĺ��"
         && me->query("gender")=="Ů��" && fam["generation"] == 4
         && fam["master_name"] != "С��Ů" ){
           me->set("family/master_name", "С��Ů");
           me->set("family/master_id", "xiao longnu");
           tell_object(me,HIG"ϵͳ�Զ������ʦ����ΪС��Ů�ˡ�\n"NOR);
           }         
}
