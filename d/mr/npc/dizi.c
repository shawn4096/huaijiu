// dizi.h
inherit NPC;
int do_clone(object me,object ob);
mapping my_skills;
mapping my_learned;
mapping valid_types = 
([
       "finger":       "ָ��",
       "hand":         "�ַ�",
       "cuff":         "ȭ��",
       "claw":         "צ��",
       "strike":       "�Ʒ�",
       "leg":          "�ȷ�"
]);

mapping *command=({
([
       "id"   : "1",
       "name" : "��������",
        "file" : "/d/suzhou/southgate",
]),
([                   
       "id"   : "2",
       "name" : "������",
        "file" : "/d/mr/yanziwu",
]),               
([                   
       "id"   : "3",
        "name" : "������������",
       "file" : "/d/xingxiu/jygw",
]),
([
       "id"   : "4",
       "name" : "��ɿ�",
       "file" : "/d/xingxiu/road2",
]),
([     
       "id"   : "5",
       "name" : "����ׯ",
       "file" : "/d/thd/guiyun/houting",
]),
([
       "id"   : "6",
       "name" : "�һ���",
       "file" : "/d/thd/jicui",
]),
([
       "id"  : "7",
       "name" : "�����´��۱���",
       "file" : "/d/shaolin/daxiong",
]),
([
       "id"  : "8",
       "name" : "���޺�",
       "file" : "/d/xingxiu/ryd",
]),
});

void init()
{
       object me = this_player();
       object ob = this_object();
       ::init();
       if (//interactive(me)  && 
		   me->query_temp("dizi")==ob &&
		   me->query("family/family_name") == "����Ľ��")
       {
               if( !ob->query("cloned") )
               {
                       ob->add_temp("apply/attack",  random(30));
                       ob->add_temp("apply/dodge",  100+random(50));
                       ob->set_temp("skill_target", me->query_temp("skill_target"));
                       ob->set_temp("skill_id", me->query_temp("skill_id"));
                       ob->set_temp("skill_lvl", me->query_temp("skill_lvl"));
                       ob->set("family/master_id", me->query("id"));
                       ob->set_temp("skill_type", me->query_temp("skill_type"));
						ob->set_temp("lead",me);
                       ob->set_leader(me);
                       if( !ob->query_temp("leader"))
                       tell_object(me, ob->name()+"��������һ���ж���\n");
//                       remove_call_out("do_clone");
                       remove_call_out("check_fight");
                       remove_call_out("dest");
                       do_clone(me,ob);
                       call_out("check_fight", 1, ob);
                       call_out("dest", 720, ob);
               }
               else 
               {
                       remove_call_out("dest");
                       remove_call_out("check_fight");
                       call_out("check_fight", 1, ob);
                       call_out("dest", 720, ob);
               }
       }
       add_action("do_touxue", "touxue");
       add_action("push", "push");
}

int do_clone(object me,object ob)
{
//       object ob;
       mapping hp_status, skill_status, map_status, prepare_status;
       string *sname, *mname, *pname;
       int i, temp;

//       ob = this_object();

/* delete and copy skills */
       ob->set("cloned", 1);
       if ( mapp(skill_status = ob->query_skills()) ) {
               skill_status = ob->query_skills();
               sname  = keys(skill_status);

               temp = sizeof(skill_status);
               for(i=0; i<temp; i++) {
                       ob->delete_skill(sname[i]);
               }
       }

       if ( mapp(skill_status = me->query_skills()) ) {
               skill_status = me->query_skills();
               sname  = keys(skill_status);

               for(i=0; i<sizeof(skill_status); i++) {
                       ob->set_skill(sname[i], skill_status[sname[i]]);
               }
       }

/* delete and copy skill maps */

       if ( mapp(map_status = ob->query_skill_map()) ) {
               mname  = keys(map_status);

               temp = sizeof(map_status);
               for(i=0; i<temp; i++) {
                       ob->map_skill(mname[i]);
               }
       }

       if ( mapp(map_status = me->query_skill_map()) ) {
               mname  = keys(map_status);

               for(i=0; i<sizeof(map_status); i++) {
                       ob->map_skill(mname[i], map_status[mname[i]]);
               }
       }

/* delete and copy skill prepares */

       if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
               pname  = keys(prepare_status);

               temp = sizeof(prepare_status);
               for(i=0; i<temp; i++) {
                       ob->prepare_skill(pname[i]);
               }
       }

       if ( mapp(prepare_status = me->query_skill_prepare()) ) {
               pname  = keys(prepare_status);

               for(i=0; i<sizeof(prepare_status); i++) {
                       ob->prepare_skill(pname[i], prepare_status[pname[i]]);
               }
       }

       hp_status = me->query_entire_dbase();

               ob->set("str", hp_status["str"]);
               ob->set("int", hp_status["int"]);
               ob->set("con", hp_status["con"]);
               ob->set("dex", hp_status["dex"]);

               ob->set("eff_jingli",hp_status["eff_jingli"]);
               ob->set("max_qi",    hp_status["max_qi"]);
               ob->set("eff_qi",    hp_status["max_qi"]);
               ob->set("qi",        hp_status["max_qi"]);
               ob->set("jingli",    hp_status["eff_jingli"]);
               ob->set("max_jingli",hp_status["max_jingli"]);
               ob->set("max_jing",  hp_status["max_jing"]);
               ob->set("eff_jing",  hp_status["eff_jing"]);
               ob->set("jing",      hp_status["eff_jing"]);
               ob->set("max_neili", hp_status["max_neili"]);
               ob->set("neili",     hp_status["max_neili"]);
               ob->set("jiali",     hp_status["jiali"]);
               ob->set("combat_exp",hp_status["combat_exp"]*2/3);
               return 1;
}

string ask_job()
{
       object me = this_player();
       object ob = this_object();
if( ob->query("family/master_id") != me->query("id"))
               return "���ֲ�����ʦ������û��Ȥ�ش�������⡣";

       return "ׯ����ʦ��������һͬ��ׯȥ͵ѧ"+ ob->query_temp("skill_lvl")+"��"+ob->query_temp("skill_target")+"["+ob->query_temp("skill_id")+"]��";
}

string ask_command()
{
       object ob = this_player();
       string str="";
        int i=sizeof(command);
if( this_object()->query("family/master_id") != ob->query("id"))
               return "���ֲ�����ʦ������û��Ȥ�ش�������⡣";
        while (i--) 
        {
               str += command[i]["name"];
               str += "(" + command[i]["id"] + ") \n";
        }

    return "��������push <id>����������ȥ��������ȥ�ĵط���\n"         + str;
}

int do_touxue(string arg)
{
        object ob, me, obj;
        string skill, skill_name, teacher;
        int master_skill, gin_cost, lvl, iii, flag=0;
        me = this_player();
        obj = this_object();
        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( !me->is_fighting() )
                return notify_fail("����ս������ô��͵ѧ�أ�\n");

        if( me->query("family/family_name") != "����Ľ��")
               return notify_fail("�㲻�ǹ���Ľ�ݵ��ӣ������Ͳ���͵ѧ��\n");

        if( me->query_skill("douzhuan-xingyi", 1) < 100 )
               return notify_fail("��Ķ�ת���Ƽ��𲻹����޷�����͵ѧ����߼����ܡ�\n");

        if(me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("������û���ö�ת���ƣ���ô��͵ѧ�����˵��书��\n");

        if(!arg || (sscanf(arg, "%s %s", teacher, skill)!=2 ))
                return notify_fail("ָ���ʽ��touxue <ĳ��> <����>\n");

        if( !(ob = present(teacher, environment(me))) || !ob->is_character())
                return notify_fail("��Ҫ��˭͵ѧ��\n");

        if( !present(this_object(), environment(me)))
               return notify_fail("��ĵ���û���������͵ѧ�˸�˭����\n");

        if( this_object()->query("family/master_id") != me->query("id"))
               return notify_fail("�Աߵ�����˺�������ĵ��Ӱɣ�\n");

        if( !living(ob) )
                return notify_fail("��....����Ȱ�" + ob->name() + "Ū����˵��\n");

        if( (int)ob->query("combat_exp", 1) < (int)me->query("combat_exp", 1)*2/3 )
               return notify_fail("�����˵��书��Ҳ͵ѧ,���ж��ˣ�\n");

    if( ob->query_temp("combat_yield") )
               return notify_fail("�������Ǵ򲻻��֣�����ô͵ѧ�����书��\n");

        for(iii=1;iii<sizeof(valid_types);iii++)
        {
                if (me->query_temp("skill_type") == valid_types[iii]) flag=1;
        }
/*        if (flag)
        {
        if( ob->query_skill_prepared(me->query_temp("skill_type")) != me->query_temp("skill_id") )
                        return notify_fail("�����ڲ���ʹ��"+me->query_temp("skill_target")+"������ô͵ѧ�����书��\n");
        }
        else
        {
        if( ob->query_skill_mapped(me->query_temp("skill_type")) != me->query_temp("skill_id") )
               return notify_fail("�����ڲ���ʹ��"+me->query_temp("skill_target")+"������ô͵ѧ�����书��\n");
        }
*/
        if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("���������±����ұ���͵ѧ�ˡ�\n");

       if( !me->query_condition("mr_job"))
               return notify_fail("�㻹û���������ء�\n");

       if( skill != me->query_temp("skill_id") )
               return notify_fail("��һ������Ҫ͵ѧ�����书ô��\n");


       lvl = obj->query_skill(skill, 1);
       if( lvl >= obj->query_temp("skill_lvl") )
       {
               write("����(Dizi)����������ĸ����㣺ׯ���������ǵ������Ѿ�����ˣ����ǻ��ǻ�������ɡ�\n");
               obj->set_temp("job_done", 1);
               return 1;
       }

        gin_cost = 800 / (int)me->query("int");


        if( ((int)ob->query("jing") > gin_cost/5 + 1 )
        &&  ((int)ob->query("jingli") > gin_cost/5 + 1 ))
        {
                if( userp(ob) )
                 ob->receive_damage("jing", gin_cost/5 + 1);
                 ob->receive_damage("jingli", gin_cost/5 + 1);
        }
        else
        {
                write("����" + ob->name() + "��Ȼ̫���ˣ����Ѿ�û�а취͵ѧ��ʲô�ˡ�\n");
                return 1;
        }


        if( (int)me->query("jing") > gin_cost && (int)me->query("jingli") > gin_cost )
        {
               if(skill_name = SKILL_D(skill)->query_skill_name(master_skill))
                        printf("����ݶ�ת���Ƶľ��裬��ϸ��ĥ��%s��ÿ������������ԡ�%s����һ���ƺ���Щ�ĵá�\n", ob->name(), skill_name);
                else
                        printf("�����͵ѧ��"+to_chinese(skill)+"�ľ��������������ĵ��ӣ���ĵ���Ҳ͵͵��ĥ��%s���������ƺ���Щ�ĵá�\n", ob->name());
                        obj->add_skill(skill, obj->query("int"));
        }
       else
       {
               gin_cost = me->query("jing");
                write("��̫���ˣ���������Ϣһ�°ɡ�\n");
        }
               if( random(100) >= 90)
               {
               message_vision("$NͻȻ������ʲô���鲻����ˣ�˫�۶���ɱ�⡣\n", ob);
                       ob->kill_ob(me);
               }


        me->receive_damage("jing", gin_cost );
        me->receive_damage("jingli", gin_cost );
       me->start_busy(2);
        return 1;
}

varargs void add_skill(string skill, int amount, int weak_mode)
{
    int spi;
        if( !find_object(SKILL_D(skill))
        &&  file_size(SKILL_D(skill)+".c") < 0 )
            error("F_SKILL: No such skill (" + skill + ")\n");

        if( !weak_mode||userp(this_object()) )
       {
                if( !mapp(my_skills) ) my_skills = ([]);
                if( undefinedp(my_skills[skill]) ) my_skills[skill] = 0;
        }

        spi = query("spi");
        if( sizeof(my_learned) > spi )
                amount /= sizeof(my_learned) - spi;

        if( !amount ) amount = 1;

        if( !mapp(my_learned) ) my_learned = ([ skill : amount ]);
        else (int)my_learned[skill] += amount;

        if( (!weak_mode||userp(this_object()))
        &&   my_learned[skill] > (my_skills[skill] + 1) * (my_skills[skill] + 1) ) {
             my_skills[skill]++;
             my_learned[skill] = 0;
             this_object()->set_skill(skill,my_skills[skill]+1);
       }
}

void accept_fight(object ob)
{
       object me = this_player();
       if( ob->query("family/master_id") == me->query("id") )
       {
               message_vision("\n$N��æ���ڵأ�˵�������Ӳ��ҡ�\n", ob);
       }
       else if( ob->query("family/family_name") == "����Ľ��")
       {
               message_vision("����ͬ��֮�䲻���භ�ɣ�\n", ob);
       }
       else
       {
               message_vision("\n$N��Ц������ƾ��Ҳ���Ҷ���\n", ob);
               ob->kill_ob(me);
       }
       return;
}

void check_fight(object ob)
{
       mapping smap, pmap;
       string type, id, *skill;
        int i;
       type = ob->query_temp("skill_type");
       id = ob->query_temp("skill_id");

       smap = ob->query_skill_map();
       pmap = ob->query_skill_prepare();
       if( ob->is_fighting())
       {
               if( ob->query_temp("skill_type") == "blade"
               ||  ob->query_temp("skill_type") == "sword"
               ||  ob->query_temp("skill_type") == "stick"
               ||  ob->query_temp("skill_type") == "staff"
               ||  ob->query_temp("skill_type") == "club"
               ||  ob->query_temp("skill_type") == "whip" )
               {
                       carry_object("/clone/weapon/"+ob->query_temp("skill_type"))->wield();
                       ob->map_skill(type, id);
//                         ob->set_skill(id, 150);
               }
                    if( ob->query_temp("skill_type") == "strike"
                    ||  ob->query_temp("skill_type") == "cuff"
                    ||  ob->query_temp("skill_type") == "leg"
                    ||  ob->query_temp("skill_type") == "claw"
                    ||  ob->query_temp("skill_type") == "hand"
                    ||  ob->query_temp("skill_type") == "finger" )
                       {
                       skill = keys(pmap);
                       for (i=0; i<sizeof(skill); i++) {
                       ob->prepare_skill(skill[i]);
                       }

                       ob->reset_action();
                       ob->map_skill(type, id);
                       ob->map_skill("parry", "canhe-zhi");
//                         ob->set_skill(id, 150);
                       ob->prepare_skill(type, id);
               }
         }
          else call_out("check_fight", 1, ob);
          return;
}                       

int push(string arg)
{
       object me = this_player();
       object ob =this_object();
       int i=sizeof(command);

       if (!arg) return notify_fail("��Ҫȥ���\n");
        if (me->is_busy() || me->is_fighting())
               return notify_fail("����æ���أ�\n");
        if (ob->is_busy() || ob->is_fighting())
               return notify_fail("����æ���أ�\n");

       if( me->query("family/family_name") != "����Ľ��")
               return notify_fail("���������ߣ��Ŷ�Ҳû�У�\n");
               
       if( ob->query("family/master_id") != me->query("id"))
               return notify_fail("���ֲ�����ʦ����ƾʲô�����˼ң�\n");
       while (i--) 
       {
               if(arg == command[i]["id"])                  
               {
               message_vision("$N����$n˵��������ȥ"+command[i]["name"]+"�����ң������͵���\n", me,ob);
               me->start_busy(3);
               call_out("do_move", 3, ob, i);
               return 1;
               }
        }
}

void do_move(object ob, int i)
{
       message_vision("\n$N�Ҵ�ææ���뿪��\n\n", ob);
       ob->move(command[i]["file"]);                      
       message_vision("\n$N�Ҵ�ææ�����˹�����\n\n", ob);
}    

void dest(object ob)
{
	if(!ob) return;
       write(ob->name()+"�Ҵ��뿪��\n");  
       destruct(ob);
	   return ;
}
