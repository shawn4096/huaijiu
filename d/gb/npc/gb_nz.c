// gaibang_npc.c, recruiting gb_dizi and promoting system
#include <ansi.h>

mixed names = ({
	({
          "��ɰ�����Ԫ�㲨", "�޾��������","��ȭ��������ȭ",
	}),
       });

mixed ids=({
          ({
            "yuan guangbo","mai jing","guo sanquan",
          }),
          });
 
mixed directory=({
                ({
                 "/d/shaolin/npc/yuan","/d/shaolin/npc/mai",
                 "/d/shaolin/npc/guo",
                 // "/u/hunthu/npc/yan",
                 //"/u/hunthu/npc/shan","/u/hunthu/npc/meng",
                 //"/u/hunthu/npc/xu", 
               }),
               });

mixed wheres=({
             ({
               "����","����","����","����","����","����",
               "�䵱ɽ","����","Ľ������","������", 
            }),
            });

mixed wherei=({
               "/d/city/bingqin","/d/city/guangchang",
                "/d/fuzhou/biaoju","/d/xiangyang/eroad1","/d/jiaxing/tieqiang",
                "/d/wudang/guangchang","/d/mingjiao/qianting","/d/mr/yanziwu",
                "/d/shaolin/ting",
               }),
               }); 

string ask_me()
{
	mapping fam, my_fam; 
        object applicant, me,ob;
	int position,xx;
	string target,weizhi,t_id,weizhi_w;
	applicant=this_player();
	me=this_object();
	my_fam  = me->query("family");
// check if this player is gb dizi and meet the requirements for promotion
     if(!applicant->query("gb_pass"))
       return "���ûΪ����������������Ȼ������?!\n";
       if ((int)applicant->query("gb_job",1)<100)
            return RANK_D->query_respect(applicant)+
           "Ϊ�Ұﹱ��̫�٣���ô�����������ҿɲ����ġ�\n";
       if ((int)applicant->query("combat_exp",1)<280000)
            return RANK_D->query_respect(applicant)+
           "�书δ�ɣ�Ϊ���г����ҿɲ����ġ�\n";                   
       if (interactive(applicant) &&
        (int)applicant->query_condition("gb_mission"))  
        return "�����ⳤ���ǵ�����û��ɣ���Ȼ��������?!\n";
        if (interactive(applicant) &&
        (int)applicant->query_condition("gb_jiaomie"))  
        return "��������ȥ����"+applicant->query_temp("promotion_target)
               +"��ô�����ȥ�ɡ�\n";
     	position=random(sizeof(names[0]));
        xx=random(sizeof(wheres[0]));
        target = names[0][position];
        weizhi = wheres[0][xx];
        t_id=ids[0][position];
        weizhi_w=wherei[0][xx];
        if (ob=find_living(t_id))
          destruct(ob);
        ob=new(directory[0][position]);   
        ob->move(weizhi_w);
        applicant->set_temp("promotion_target", target);
        applicant->apply_condition("gb_jiaomie",60);
        return target+"�����°��ڶ��в��壬�����Ѿ���������׷ɱ��\n"
               +"���������Ѿ��ŷ��Ӵ���"+weizhi+"һ�����㼴�̳���\n"
               +"���������˵����ջ���������ҡ�\n";     
}     



/*string ask_job()
{
  object applicant, me;
  int exp,position;
  string target;
   applicant=this_player();
   me=this_object();
   if(!applicant->query("gb_pass"))
   return "��û��ͨ���������ӵĿ��飬�ҿɲ������㡣\n";
    exp=(int)applicant->query("combat_exp",1); 
    if(exp>1500000)
      return "�������ո�ǿ�����¿ɲ����ͷ����ϡ�\n";
     if (interactive(applicant) &&
            	(int)applicant->query_condition("gb_mission"))  
       return "����ȥɱ"+applicant->query_temp("promotion_target")+"������ȥ��\n";
    if (interactive(applicant) &&
      	(int)applicant->query_condition("gb_busy"))  
         return " �����ҿ�û�и�������񣬵Ȼ������ɡ�\n";
    if(exp>=700000)
         position=5;
     else if(exp>=300000)
         position=4;
     else if(exp>=100000)
          position=3;
     else if(exp>=50000)
          position=2;
     else
          position=1;
 	target = names[position-1][random(sizeof(names[position-1]))];
        applicant->set_temp("promotion_target", target);
        applicant->set_temp("assigned_by", me->query("name"));	
        applicant->apply_condition("gb_mission",30);
        applicant->apply_condition("gb_busy",10);
        return "�ðɣ���ȥ��" + target +"�⹷����ɱ�ˣ�������ͷ�����ң�\n";
}*/
 int accept_object(object who, object ob,object me)
{
//        int val;
//        object me = this_object();
// check if accept corpse from player

        if ( !who->query("gb_pass")) 
              return 0;
        if ( ob->query("id") != "qing zhuling" ) {
		command("say �ⶫ����Ҫ��û�á�");
		return 0;
	}
        if ( !who->query_temp("promotion_target") ) {
		command("say �ð��������������������");
                return 0;
	}

/*        if ( who->query_temp("assigned_by") != me->query("name") ) {
		command("say �����ģ�����ȥ����������Ķ����ɡ�");
                return 0;
        }*/

// all right, now it's time to check if the corpse is correct ;
// there is still a bug here, since i can't check if corpse is 
// npc's corpse or a player who has the same name as that npc, 
// although it's illegal.
/*	if ( ob->query("kill_name") 
	!= who->query_temp("promotion_target") ) {
		command("say �ٺ١���������ɱ�����ˡ�");
		return 0;
	}*/
/*	if ( ob->query("victim_user") ) { 	  // is it player's corpse?
		command("say " + RANK_D->query_rude(who) + 
			"����Ȼ����ƭ�����ϣ��������ѣ�");
		call_out("killing_object",1,who);
		return 0;
	}*/

// benifits from ����, 10 maxneili + 1 begging,sttealing level
	command("applaud " + who->query("id"));
        command("say ���úã������������Ǳ��ﱾɫ��\n");
//        me->add_money("gold",10);
  //      command("give gold to"+who->query("id"));         
//        val=1+random(9); 
        call_out("destroying", 1, me, ob);           
        who->add("potential",100+random(100));
         if (who->query("potential") > who->query("max_pot"))
                who->set("potential", who->query("max_pot"));   
        who->add("combat_exp",1200);
        who->add("gb_job",5);
//	who->delete_temp("assigned_by");
	who->delete_temp("promotion_target");
        who->clear_condition("gb_jiaomie");
	return 1;
       }
/*         who->add("potential",random(10+who->query("max_pot")/3)*2);
         if (who->query("potential") > who->query("max_pot"))
             who->set("potential", who->query("max_pot"));   
        who->add("combat_exp",(1+random(8))*100);
        who->set("gb_job",2);
	who->delete_temp("assigned_by");
	who->delete_temp("promotion_target");
        who->clear_condition("gb_mission");
	return 1;*/
}	


void killing_object(object who)
{
	object me = this_object();
	me->kill_ob(who);
	who->unconcious();
}


void gb_apprentice(object ob)
{
        string prev_family_name;

        if ( (int)ob->query("gb_bags") >= 2  
	&& (prev_family_name = ob->query("family/family_name")) != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                return;
        }
        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        if ( prev_family_name != "ؤ��")
                ob->set("gb_bags", 1);
        ob->set("title",sprintf("ؤ��%s������",
                chinese_number(ob->query("gb_bags"))) );
}
/* void gbzl_apprentice(object ob)
{
        string prev_family_name;

        if ( (int)ob->query("gb_bags") >= 2  
	&& (prev_family_name = ob->query("family/family_name")) != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                return;
        }
        if ( prev_family_name != "ؤ��"){
                 if((int)ob->query("jobs")<2000)
                     command("say ��Ϊؤ��δ��ȫ�����һ�Ҫ����ı��֡�\n");
                      return;
                     command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�Ϊ����Ч�����ڰ�����ǰ��һ���õı��֡�\n");
        command("recruit " + ob->query("id"));
                    ob->set("gb_bags", 6);
                    ob->set("title",sprintf("ؤ��%s������",
                  chinese_number(ob->query("gb_bags"))) );
                   return;
          }
            if((int)ob->query("gb_bags")<6)
              {                      
               command("say + RANK_D->query_respect(ob)+�ڰ���������ǳ��Ҫ����Ŭ����\n");
               return;
              }
        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�Ϊ����Ч�����ڰ�����ǰ��һ���õı��֡�\n");
        command("recruit " + ob->query("id"));
        return;
    }*/
void destroying(object me, object obj)
{
	destruct(obj);
	return;
}
