// huo.c ��ʦ��.����
// by snowman 12.feb.98
// Modify by Looklove 2000/10/07

#include <ansi.h>
inherit NPC;
string ask_me();
void check_skills(object ob);
int waiting(object me, object dest);
int checking(object me, object dest);
int do_back(object me);
int do_kill(object me, object dest);
int do_weapon(object me);
void change_huo();

void create()
{
	object me = this_object(); 
     	remove_call_out("create");
     	if (clonep()) tell_room(environment(me),
      	HIY +"����ת��ǽ�Ǻ�Ȼ�����ˣ������߳���һ������ޱȵ���ؤ��\n\n" NOR, ({me}));
     	me->set_name("��ʦ��", ({"he shiwo", "he", "shiwo"}));     
     	me->set("gender", "����");
     	me->set("title", "ؤ���ʮ�Ŵ�����");      
     	me->set("age", 35);
     	me->set("unique", 1);
     	me->set("per", 13);
     	me->delete("huodu");
     	me->set("location", 1);
     	me->set("long", "ֻ��������һ��������õĺ��£��ֳ�һ���Ʊ��ڴ�ϸ�����ȣ���ͷ
		�ҷ���һ��������ӷ�װ���͹͹�����ǰ̺ۣ����ϸ�����ֻ������ԭ
		����һ��������ӡ�\n"); 
     
     	me->set("attitude", "friendly");
     	me->create_family("ؤ��", 19, "����");
     	me->set("str", 23);
     	me->set("int", 24);
     	me->set("con", 22);
     	me->set("dex", 27);  
     	me->set("per", 12);  
     	me->set("chat_chance", 35);
     	me->set("chat_msg", ({ (: random_move :), }));
        me->set("max_qi", 700);
        me->set("max_jing", 700);
        me->set("jingli", 500);
       if (clonep()) me->reincarnate();         
        me->set("combat_exp", 150000);
        me->set_skill("parry", 60);
        me->set_skill("force", 60);
        me->set_skill("dodge", 60);
        me->set_skill("staff", 60);
        me->set_skill("huntian-qigong", 60);       
        me->set_skill("tianshan-zhang", 60);      
        me->set_skill("xiaoyaoyou", 50);
        me->set_skill("suohou-shou", 50);
        me->set_skill("hand", 50);
        me->map_skill("force", "huntian-qigong");
        me->map_skill("dodge", "xiaoyaoyou");
        me->map_skill("hand", "suohou-shou");
        me->map_skill("staff", "tianshan-zhang");
        me->prepare_skill("hand", "suohou-shou");        
        me->set("inquiry", ([ 
            "����"  : (: ask_me :), 
            "ؤ��" : "����ؤ�������µ�һ��\n",                    
            "���ַ���" : "����˵ʲô����",
            "�����" : "����˵ʲô����",
            "������" : "����˵ʲô����",
            "��Ħ��" : "����˵ʲô����",            
       ]) ); 
        if (clonep()) do_weapon(me);
        setup();               
        remove_call_out("change_huo");          
        if(clonep())
           call_out("change_huo", 900, me);
}       

int do_weapon(object me)
{
   object armor, weapon, *ob;
   int i;
   if(!me) return 0;
   ob = all_inventory(me);
  
   for(i=0; i<sizeof(ob); i++) destruct(ob[i]); 
   if (query("huodu")) armor = new(ARMOR_D("pao2"));
   else armor = new(ARMOR_D("cloth"));
   armor->move(me);
   armor->wear();
   if (query("huodu")) weapon = new(__DIR__"obj/txs");
   else weapon = new(BINGQI_D("gangzhang"));
   weapon->move(me);
   weapon->wield();
   me->add_money("silver", 50);
   return 1;
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && visible(ob)){
           if(query("huodu") && ob->query("combat_exp") > 100000) check_skills(ob);
           if(present("yuzhu bang", ob)){      
               message_vision(BLU"$NͻȻ����$n��ǰ���۾�ֱ����$n������������\n"NOR,me,ob); 
               change_huo();
               ob->start_busy(2); 
               do_kill(me, ob);                                              
               }
           }
}

string get_user_place()
{
        object *obs = users(), ob, room;

        ob = obs[random(sizeof(obs))];  
        room = environment(ob);
        
        if (wiz_level(ob)
        || ob->is_ghost()
        || !room
        || strsrch(file_name(room),"/d/") < 0 
        || !strsrch(base_name(room), "/d/wizard/")
        || !strsrch(base_name(room), "/d/death/")
        || !strsrch(base_name(room), "/d/wuguan/")) 
                return get_user_place();

        else return file_name(room);
                
}
int do_back(object me)
{    
        string room;
        
        remove_call_out("do_back");
        if (!stringp(room = get_user_place()))          
                me->move("/d/city/kedian");
        else me->move(room);  
                             
        tell_room(environment(me), me->query("name")+"�첽���˹�����\n", ({me}));       
        me->set_leader(0);
        return 1;
}

string ask_me()
{
        object ob,me;
        ob=this_player();
        me=this_object();
        if(ob->query("combat_exp") < 100000)
           return "С���ӣ����Լ�������֪����ôд�𣿱��ʶ������ġ�\n";
        else{
            if (query("huodu")){
                remove_call_out("check_skills");
                check_skills(ob);
                return "�ٺ٣��������Ǳ����ӣ���ˣ���׺�Ϸ���ҿ����ɣ�\n";
                }
            else{ 
             switch(random(4)) {
               case 0 : return "��֪����\n"; break;
               case 1 : return "�ҿɲ���ʶ����ˡ�\n"; break;       
               case 2 : return "˭�ǻ�������\n"; break;       
               case 3 : change_huo(); 
                        do_kill(me, ob); 
                        return "�ٺ٣��������Ǳ����ӣ���ˣ���׺�Ϸ���ҿ����ɣ�\n";       
                        break;       
                        }                      
            }
         }
}

void change_huo()
{
        int i;
        object *ob, me;
        remove_call_out("change_huo");
        me = this_object();  
  
     tell_room(environment(me), HIY +"ͻȻ��ʦ������һЦ�����ֳ�ȥ���ϵİ��಼�£���������һĨ����Ȼ
		ת�۾ͱ����һλ���Ž��ۡ������������깫�ӡ�\n\n" NOR, ({me}));        
        me->set("title", "�ɹ�����");   
        me->set("long", "ֻ�������ױ���ɫ���ۣ�����ߡ�ȣ�
		�����Ӵ�磬����һ�ɰ���֮ɫ��\n");           
        me->set_name("����", ({"huo du", "huo", "du"}));
        me->set("shen", -12000);
        me->set("per", 25);
        me->set("huodu", 1);
        me->set_skill("parry", 100);
        me->set_skill("force", 100);
        me->set_skill("dodge", 100);
        me->set_skill("sword", 100);
        me->set_skill("songshan-qigong", 120);       
        me->set_skill("songshan-jian", 120);      
        me->set_skill("xiaoyaoyou", 120);
        me->set_skill("suohou-shou", 120);
        me->set_skill("hand", 100);
        me->map_skill("force", "songshan-qigong");
        me->map_skill("dodge", "xiaoyaoyou");
        me->map_skill("hand", "suohou-shou");
        me->map_skill("sword", "songshan-jian");
        me->prepare_skill("hand", "suohou-shou");
        me->set("combat_exp", 300000);
        me->set("max_qi", 1500);
        me->set("max_jing", 1300);
        me->set("eff_jingli", 1400);
        me->set("jiali", 50);
        me->reincarnate();   
        me->set("chat_chance_combat", 20);
        me->set("chat_msg_combat", ({ (: perform_action, "sword.feiwu" :) }));  
        if (!environment()->query("no_fight")) {
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
                if(!userp(ob[i])) continue;
                if(me->query_temp("block_msg/all")) continue;
                if(!living(me))continue;
             	if(ob[i]->query("combat_exp") < 100000) continue;
                COMBAT_D->do_attack(me, ob[i], me->query_temp("weapon"),1);
        }
        }
        do_weapon(me);
        remove_call_out("create");
        if (clonep())
            call_out("create", 300+random(200), me);           
}

void kill_ob(object ob)
{       
      if (query("huodu")) return;  
      else change_huo(); 
}

void reset()
{
  if (clonep()) do_back(this_object());
}
#include "killer.h";
