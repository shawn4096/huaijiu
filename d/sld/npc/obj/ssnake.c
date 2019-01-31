// ssnake

#include <ansi.h>
inherit NPC;

int snakehd();
int snake_attack_ob(object ob);
void create()
{
        set_name("����", ({ "jin she","snake","she" }) );       
        set("race", "Ұ��");
        set("long", "���������������С�ߡ�\n");
        set("limbs", ({ "ͷ��", "����", "�ߴ�", "β��" }) );
        set("verbs", ({ "bite" }) );
        set("combat_exp", 100000);  
        set("no_return",1);
        set("no_clear_up",1);

        set("attitude", "friendly");
        setup();
}

void do_command(string arg)     
{
       string dir,* str;
       object owner,tar;
    
       if(!arg || arg=="") return;
       if( strsrch(arg, "rumor") != -1
       || strsrch(arg, "party") != -1
       || strsrch(arg, "sj") != -1
       || strsrch(arg, "chat") != -1 )
             	return;
             	
       if(!strsrch(arg,"kill",1) || !strsrch(arg,"fight",1) || !strsrch(arg,"hit",1)){
         owner = query("owner");
         if(!objectp(present(owner->query("id"), environment(this_object())))){
             tell_object(owner,"�㲻���ý��߹������ˡ�\n");
             return;
         }
         else {
             str=explode(arg, " ");
             if(sizeof(str) < 2 || (objectp(tar=present(str[1], environment(this_object()))) && userp(tar))){
                tell_object(owner,"�㲻���ý��߹������ˡ�\n");
                return;
             }               
         }
       } 
        if(!strsrch(arg,"vote",1)){
            tell_object(query("owner"),"�㲻���ý���ͶƱ! \n");
         return; }
       if(!strsrch(arg,"get",1)){
         tell_object(query("owner"),"�㲻���ý���get������\n");
         return;
       }
       if(!strsrch(arg,"give",1)){
         tell_object(query("owner"),"�㲻��give���������ߡ�\n");
         return;
       }
       switch(arg){
        case "e": dir="east"; break;
        case "w": dir="west"; break;
        case "n": dir="north"; break;
        case "s": dir="south"; break;
        case "ne": dir="northeast"; break;
        case "nw": dir="northwest"; break;
        case "se": dir="southeast"; break;
        case "sw": dir="southwest"; break;
        case "u":  dir="up"; break;
        case "d":  dir="down"; break;
        case "nu": dir="northup"; break;
        case "eu": dir="eastup"; break;
        case "su": dir="southup"; break;
        case "wu": dir="westup"; break;
        case "nd": dir="northdown"; break;
        case "ed": dir="eastdown"; break;
        case "sd": dir="southdown"; break;
	case "wd": dir="westdown"; break;
        default: dir=arg; break;
       }
       set_name(query("owner")->query("name")+"�Ľ���", ({ query("owner")->query("id")+"'s jin she"}) );  
       command(dir);
       switch(dir) {
         case "east": command("look"); break;
         case "west": command("look"); break;
         case "north": command("look"); break;
         case "south": command("look"); break;
         case "northeast": command("look"); break;
         case "northwest": command("look"); break;
         case "southeast": command("look"); break;
         case "southwest": command("look"); break;
         case "up": command("look"); break;
         case "down": command("look"); break;
         case "northup": command("look"); break;
         case "eastup": command("look"); break;
         case "southup": command("look"); break;
         case "westup":  command("look"); break;
         case "northdown": command("look"); break;
         case "eastdown": command("look"); break;
         case "southdown": command("look"); break;
	 case "westdown": command("look"); break;
         case "enter": command("look"); break;
         case "out": command("look"); break;
         default: break;
       }
       set_name("����", ({ "jin she","snake","she" }) );     
}

void relay_message(string msgclass, string msg)
{
       object owner;
       string *ary;
       int i;
        
       msg = "1\n" + msg;
       ary = explode(msg, "\n");
       owner = query("owner");
       if(objectp(owner) && !owner->is_ghost()){
         if( environment(this_object()) == owner ) return;
         if(owner->query_temp("wieldsnake",1)) return;
         for (i=1;i<sizeof(ary);i++)
           if (owner) tell_object(owner,HIG"���ߡ�"NOR+ary[i]+NOR+"\n");
       }                                               
}

int hit_ob(object me, object victim, int damage)
{
       victim->apply_condition("snake_poison", victim->query_condition("snake_poison")+ 5);
        return 0;
}

int snakehd()
{
       object owner,me,weapon;
       object * ob;
       int i;

       if(!this_object()) return 1;
       owner=query("owner");
       me=this_object();
       if( !objectp(owner)
        || !owner->query_temp("mysnake",1)
        || owner->query_temp("mysnake",1)!=me ){
         destruct(me);
         return 1;
       }
       if(owner->is_ghost()){
	 me->die();
         return 1;
       }
       if(userp(environment(me)) && (environment(me)!=owner)){
         me->move(owner);
         message_vision("����һ�����ֻص���$N���ϡ�\n",owner); 
         call_out("snakehd",1);
         return 1;
       }  
    if(((owner->query("qi")<=owner->query("max_qi")*3/10) || (owner->query("eff_qi")<=owner->query("max_qi")*2/5)) &&
    owner->is_fighting() && environment(owner)->query("no_death")==0 && ! random(10)) {
               if(file_name(environment(me))=="/d/sld/emptyroom"){
        ob = all_inventory(owner);
        for(i=0; i<sizeof(ob); i++){
            if(ob[i]->query("id")=="jin she"){ 
                destruct(ob[i]);
                break; }}
        me->move(owner); }
        if(environment(me)==owner) {
        me->set_temp("no_fight", 1);
        me->move(environment(owner));
        message_vision("$N�����²���,æ�ѽ������Է���ȥ��\n",owner);
        ob = all_inventory(environment(owner));
        for(i=0; i<sizeof(ob); i++){
            if(owner->is_fighting(ob[i])) 
            { me->kill_ob(ob[i]); 
            ob[i]->kill_ob(me); }} 
        owner->remove_all_killer(); 
        if(owner->query_temp("mysnake",1)==this_object()){ 
            owner->delete_temp("havegetsnake");
            owner->delete_temp("mysnake");
            owner->delete_temp("wieldsnake"); }
            return 1; }}
       if(owner->query_temp("wieldsnake",1)!=0){
         weapon=owner->query_temp("weapon");
         if((!weapon
          || weapon->query("skill_type") != "whip"
          || weapon->query("id")!="jin she" )
          && ((int)owner->query_temp("lingshe/chan",1)!=1)){
            ob = all_inventory(owner);
            for(i=0; i<sizeof(ob); i++){
             if(ob[i]->query("id")=="jin she"){
               break;    
             }
         }
         if(i>=sizeof(ob)){
            me->die();
         }
	 else call_out("snakehd",1);
         return 1;       
         }
         ob = all_inventory(environment(owner));
         for(i=0; i<sizeof(ob); i++){
           if(wizardp(ob[i]) || !living(ob[i]) || ob[i]==this_player()) continue;
           if(!owner->is_fighting(ob[i]))  continue;
           if(snake_attack_ob(ob[i]))  break;
         }
         if(i>=sizeof(ob)){
          if(random(15)==0)
             tell_room(environment(owner), me->name() + "��ͷһ��һ����˻˻������\n");
         }
       }
       else if(file_name(environment(me))=="/d/sld/npc/obj/emptyroom"){
          ob = all_inventory(owner);
          for(i=0; i<sizeof(ob); i++){
	  if(ob[i]->query("id")=="jin she"){ 
                destruct(ob[i]);
                break;    
            }
          }
          me->move(owner);
       }
       call_out("snakehd",1);
       return 1;
}

int snake_attack_ob(object ob)
{
       int dis,att,dam,olev,force,mexp,oexp,def,ar,condi,bf;
       object owner;

       if(ob->is_busy())
       {
           bf=2;
       }
       else
       {
           if(random(ob->query_kar()) > 20 ) return 0;
           else bf=1;
       }
       owner=query("owner");
       message_vision("����ͻȻ��$N�ݺݵ�һ��ҧ�¡�\n",ob);  
       dis= (int)ob->query_skill("dodge");
       dis= dis* ob->query_kar()*ob->query_dex();
       olev= owner->query_skill("dodge") * owner->query_dex();
       if( random(dis)/(random(olev)+1) > 10*(bf+1) 
        || owner->query_temp("combat_yield")){
          message_vision("$N���Ա�һ�������˿�ȥ��\n",ob);
          return 1;
       }
       else{
          message_vision("$N����������������һ��ҧ�У�\n",ob);
          tell_object(ob, "��е�һ���ʹ��������æ�˹�������\n");
          if( !owner->is_killing(ob)){
             owner->kill_ob(ob);
	     ob->kill_ob(owner);
          }
          condi = ob->query_condition("ssnake",1);
          if(!condi){
            ob->set_temp("back/damage",ob->query_temp("apply/damage",1));
            ob->set_temp("back/attack",ob->query_temp("apply/attack",1));
            ob->apply_condition("ssnake", 3);
          }
        force=100+random(401);
          mexp= owner->query("combat_exp")/1000;    
          oexp= ob->query("combat_exp")/1000; 
          def=(int)ob->query_temp("apply/defense",1);  
          ar=(int)ob->query_temp("apply/armor",1);
          if( ar < 1 ) ar =1;
          if( def < 1) def =1;
          if( oexp < 1) oexp=1;
          att = (int)owner->query_temp("apply/attack",1)/def+mexp / oexp;
          dam = (int)owner->query_temp("apply/damage",1)/ar+mexp / oexp;
    if(att < 5) att = 5;
          else if(att > 20) att = 20;
          ob->add_temp("apply/attack",-att);
	  ob->add_temp("apply/defense",-att);
          if(force >= ob->query("neili"))
            ob->set("neili",0);
          else
            ob->add("neili", - force);
            if(dam<5) dam=5;
          else if(dam > 20) dam = 20;
          if(ob->query_temp("apply/damage",1) <= dam)
            ob->set_temp("apply/damage", 0);
          else 
            ob->add_temp("apply/damage", -dam);
	  if(ob->query_temp("apply/armor",1) <= dam)
            ob->set_temp("apply/armor", 0);
          else 
            ob->add_temp("apply/armor", -dam);
       }
       call_out("check_fight", 1, ob ,owner);
       return 1;
}

void check_fight(object ob,object owner)
{
      if(!ob) return;
      if( !ob->query_condition("ssnake",1)) return;
      if(environment(ob) != environment(owner)){
          ob->set_temp("apply/attack", ob->query_temp("back/attack", 1));
          ob->set_temp("apply/damage",ob->query_temp("back/damage",1));
          ob->clear_condition("ssnake");
      }
      else if(!owner || !owner->is_fighting(ob)){
          ob->set_temp("apply/attack", ob->query_temp("back/attack", 1));
          ob->set_temp("apply/damage",ob->query_temp("back/damage",1));
          ob->clear_condition("ssnake");
      }
      call_out("check_fight", 1, ob, owner);
}

void die()
{
      object owner;

      owner=query("owner");
      if(objectp(owner) && userp(owner) && owner->query_temp("mysnake",1)==this_object()){
        owner->delete_temp("havegetsnake");
        owner->delete_temp("mysnake");
        owner->delete_temp("wieldsnake");
      }
      ::die();
}

void unconcious()
{ 
      die();
}
