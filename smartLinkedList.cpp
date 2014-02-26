//
//  main.cpp
//  dev2
//
//  Created by Ashok  on 2/26/14.
//  Copyright (c) 2014 Ashok . All rights reserved.
//

#include <iostream>
#include <map>
#include <stack>

#ifndef rc_Debug
//#define rc_Debug
#endif


using namespace std;
class LinkedList:public std::enable_shared_from_this<LinkedList>
{
    int data;
    std::shared_ptr<LinkedList>  next;
    std::shared_ptr<LinkedList> prev;
    
public:
    
   typedef struct sum
    {
        shared_ptr<LinkedList> sum = NULL;
        int carry = 0;
    } result;
    
    std::shared_ptr<LinkedList> getnext()
    {
        return next;
    }
    
    void setnext(shared_ptr<LinkedList> &src)
    {
        next = src;
    }
    
    std::shared_ptr<LinkedList> getprev()
    {
        return prev;
    }
    
    LinkedList(int val):data(val),next(NULL) , prev(NULL){};
    
    ~LinkedList(){};
    
    int getdata()
    {
        return data;
    }
    
    static void print(std::shared_ptr<LinkedList> head)
    {
        while(head != NULL)
        {
            cout << head->data;
            head = head->next;
        }
        
        std::cout << endl;
    }
    

    static shared_ptr<LinkedList> loopstart(shared_ptr<LinkedList> head)
    {
        shared_ptr<LinkedList> slow = head , fast = head;
        
        while(fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            if(fast == NULL) return  NULL;
            slow = slow->next;
            
            if(fast == slow) break;
        }
        
        slow = head;
        if(fast == NULL)return NULL;
        
        while(slow != fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
    
    static std::shared_ptr<LinkedList> sums(std::shared_ptr<LinkedList> head1 , std::shared_ptr<LinkedList> head2 , int carry)
    {
      int sum = carry;
        
      if(head1 == NULL && head2 == NULL && carry == 0)
      {
          return NULL;
      }
    
        if (head1 != NULL)
        {
            sum += head1->data;
        }
        
        
        if (head2 != NULL)
        {
            sum += head2->data;
        }
        
       
        
        std::shared_ptr<LinkedList> s = shared_ptr<LinkedList>(new LinkedList(sum%10));
#ifdef rc_Debug
        cout << sum << "head1" << head1->data << "head2" << head2->data << endl;
#endif
        
        if(head1 != NULL || head2 != NULL)
        {
            int c = sum >= 10 ? 1 : 0;
            s->next = sums(head1 != NULL ?head1->next : NULL , head2 != NULL ?head2->next : NULL,c);
        }
        
        return s;
    }
    
    static int getsize(std::shared_ptr<LinkedList> head)
    {
        int count = 0;
        
     
        while(head != NULL)
        {
            count++;
            head = head->next;
        }
        return count;
    }
    
    shared_ptr<LinkedList> padlist(shared_ptr<LinkedList> head , int lens)
    {
        if(head == NULL)
        {
            return NULL;
        }
        for(int i = 0 ; i < lens ; i++)
        {
        shared_ptr<LinkedList> temp = shared_ptr<LinkedList>(new LinkedList(0));
        temp->next = head;
        head = temp;
        }
        return head;
    }
    
    static std::shared_ptr<LinkedList> appendbefore(std::shared_ptr<LinkedList> head , int val )
    {
        std::shared_ptr<LinkedList> temp = shared_ptr<LinkedList>(new LinkedList(val));
        temp->next = head;
        head = temp;
        
        return head;
        
    }
    
    static std::shared_ptr<result> addh(std::shared_ptr<LinkedList> head1 , std::shared_ptr<LinkedList> head2 )
    {
    if(head1 == NULL && head2 == NULL)
    {
        return shared_ptr<result>(new result);
    }
        shared_ptr<result> res = addh(head1->next , head2->next);
        int val = head1->data + head2->data + res->carry;
        shared_ptr<LinkedList> head = appendbefore(res->sum, val % 10);
        res->sum = head;
        res->carry = val/10;
        
        return res;
        
        
    }
    
    static std::shared_ptr<LinkedList> sums2(std::shared_ptr<LinkedList> head1 , std::shared_ptr<LinkedList> head2 )
    {
        if(getsize(head1) > getsize(head2))
        {
            head2 = head2->padlist(head2 , getsize(head1) - getsize(head2));
        }
        
        else if(getsize(head1) < getsize(head2))
        {
                    head1 = head1->padlist(head1 , getsize(head2) - getsize(head1));
        }
        
        shared_ptr<result> res = addh(head1 , head2);
        if(res->carry == 0)
        {
            return res->sum;
        }
        else{
           return appendbefore(res->sum, res->carry);
        }
      
    }
    
    std::shared_ptr<LinkedList> insert(int data)
    {
        next = shared_ptr<LinkedList>(new LinkedList(data));
        next->prev = shared_from_this();
        return next;
        
    }
    
    static LinkedList kth(std::shared_ptr<LinkedList> head , int &count , int k)
    {
        if(head == NULL)
        {
            return NULL;
        }
        
        LinkedList node = kth(head->next , count , k);
        
        count++;
        
        if(count == k )
        {
            return *head;
        }
        
        return node;
    }
    
    static LinkedList kth2(std::shared_ptr<LinkedList> head , int k )
    {
        std::shared_ptr<LinkedList> first = head , second = head;
        
        for (int i = 0; i < k-1; i++) {
            if(second == NULL) return NULL;
            
            second = second->next;
            
            if (second==NULL) {
                return  NULL;
            }
        }
        
        while (second->next!=NULL) {
            second = second->next;
            first = first->next;
        }
        
        return *first;
        
            
        
        
    }
    
    static std::shared_ptr<LinkedList> removeduplicates2(std::shared_ptr<LinkedList> head)
    {
      
        std::shared_ptr<LinkedList> temp = head;
        
        std::shared_ptr<LinkedList> runner;
        while(temp != NULL)
        {
       
                
            runner = temp;
            while(runner->next != NULL)
            {
                if (temp->data == runner->next->data) {
                    runner->next = runner->next->next;
                }
                else
                {
                    runner = runner->next;
                    shared_ptr<LinkedList>next = runner->next;
                    if(next != NULL)
                    {
                        next->prev = runner;
                    }
                }
            }
            
            temp = temp->next;
        }
        return head;
    
    }
    
    bool deletenode(std::shared_ptr<LinkedList> head)
    {
        if (head == NULL||head->next == NULL) {
            return false;
            
        }
        
        std::shared_ptr<LinkedList> next = head->next;
        head->data = next->data;
        head->next = next->next;
        
        return true;
        
        
    }
    
    std::shared_ptr<LinkedList> partition2(int val , std::shared_ptr<LinkedList> head)
    {
        std::shared_ptr<LinkedList> b1,n1;
        
        while(head != NULL)
        {
            std::shared_ptr<LinkedList> next = head->next;
            head->next = NULL;
            if (head->data <= val) {
                if(b1 == NULL)
                {   b1 = shared_ptr<LinkedList>(new LinkedList(head->data));
                   
                }
                else{
                    
                    shared_ptr<LinkedList> n = shared_ptr<LinkedList>(new LinkedList(head->data));
                    n->next = b1;
                    b1 = n;
                    
                }
            }
            else{
                if(n1 == NULL)
                {   n1 = shared_ptr<LinkedList>(new LinkedList(head->data));
                    
                }
                else{
                    
                    shared_ptr<LinkedList> n = shared_ptr<LinkedList>(new LinkedList(head->data));
                    n->next = n1;
                    n1 = n;
                    
                }
                
            }
            
            head = next;
        }
        
        shared_ptr<LinkedList> nh = b1;
        
        if(b1 == NULL) {return n1;}
        else{
            
            while(b1 ->next != NULL)
            {
                b1 = b1->next;
            }
            b1->next = n1;
            return nh;
        }
        
    }
    
    std::shared_ptr<LinkedList> partition(int val , std::shared_ptr<LinkedList> head)
    {
        std::shared_ptr<LinkedList> b1,b2,n1,n2;
        
        while(head != NULL)
        {
            std::shared_ptr<LinkedList> next = head->next;
            head->next = NULL;
            if (head->data <= val) {
                if(b1 == NULL)
                {   b1 = shared_ptr<LinkedList>(new LinkedList(head->data));
                    b2 = b1;
                }
                else{
                    
                    shared_ptr<LinkedList> n = shared_ptr<LinkedList>(new LinkedList(head->data));
                    b2->next = n;
                    b2 = n;
                    
                }
            }
            else{
                if(n1 == NULL)
                {   n1 = shared_ptr<LinkedList>(new LinkedList(head->data));
                    n2 = n1;
                }
                else{
                    
                    shared_ptr<LinkedList> n = shared_ptr<LinkedList>(new LinkedList(head->data));
                    n2->next = n;
                    n2 = n;
                    
                }
                
            }
            
            head = next;
        }
        
        if(b1 == NULL) {return n1;}
        else{
            b2->next = n1;
            return b1;
        }
        
    }
    
    typedef struct res2
    {
        bool istrue;
        shared_ptr<LinkedList> res;
        
        res2(bool val , shared_ptr<LinkedList> value)
        {
            istrue = val;
            res = value;
        }
    } result2;
    
    friend shared_ptr<result2> ispalindrome2(std::shared_ptr<LinkedList> head , int ref)
    {
        if(head == NULL || ref <= 0)
        {
            return shared_ptr<result2>(new result2(true , NULL));
        }
        else if(ref == 1)
        {
            return shared_ptr<result2>(new result2(true , head->next));
        }
        else if(ref == 2)
        {
           return shared_ptr<result2>(new result2( head->next->data == head->data,head->next->next ));
        }
        
        shared_ptr<result2 > res2 = ispalindrome2(head->next , ref -2);
        
        if(res2->res == NULL || !res2->istrue)
        {
            return res2;
        }
        else{
             res2->istrue = res2->res->data == head->data;
            res2->res = res2->res->next;
           
            return res2;
        }
        
        
    }
    
    static bool ispalindrome(std::shared_ptr<LinkedList> head)
    {
      
        std::stack<LinkedList> stackl;
        
        std::shared_ptr<LinkedList> fast = head,slow = fast;
        
        while(fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
             stackl.push(*slow);
            slow = slow->next;
           
        }
        
        if(fast != NULL){
            slow = slow->next;
        }
        
        while(slow != NULL)
        {
            LinkedList a = stackl.top();
            stackl.pop();
            
            if(a.data != slow->data)
            {
                return false;
            }
            slow = slow->next;
            
        }
        
        return true;
    }
    
    static std::shared_ptr<LinkedList> removeduplicates(std::shared_ptr<LinkedList> head)
    {
        std::map<int, bool> map;
        std::map<int, bool>::iterator  mit = map.begin();
        std::shared_ptr<LinkedList> temp = head;
        
        std::shared_ptr<LinkedList> prev;
        while(temp != NULL)
        {
            if(map.find(temp->data)!= map.end()) {
            
            
                prev->next = temp->next;
               
                std::shared_ptr<LinkedList> next = temp->next;
                
                if(next != NULL)
                {
                    next->prev = prev;
                }
                
                temp = temp->next;
            }
            
            else{
                map.insert(mit , std::pair<int, bool>(temp->data,true));
                prev = temp;
                temp = temp->next;
                
            }
            
        
        }
        
        return head;
    }
};

shared_ptr<LinkedList::result2> ispalindrome2(std::shared_ptr<LinkedList> head , int ref);

int main(int argc, const char * argv[])
{

    shared_ptr<LinkedList> head = shared_ptr<LinkedList>(new LinkedList(9)) , printref = head;
    
    for(int count = 2 ; count < 4 ; count ++)
    {
       head = head->insert(count);
    }
    
   head = head->insert(2);
   head = head->insert(9);

   
   
   
    
    std::shared_ptr<LinkedList> h = head->partition(1, printref);
     
    
    head = shared_ptr<LinkedList>(new LinkedList(9)) , printref = head;
    
    for(int count = 2 ; count < 4 ; count ++)
    {
        head = head->insert(count);
    }
    
    head = head->insert(2);
    head = head->insert(9);
    
    /
    LinkedList::print(printref);
    
    /** Member Function tools *****/
    //head->deletenode(head->getprev());
    
    //LinkedList::removeduplicates2(printref);
    
   // LinkedList::print(h);
   //  cout << LinkedList::loopstart(printref)->getdata();
    if(ispalindrome2(printref , printref->getsize(printref))->istrue)
        cout << "YAYY";
   
   
    return 0;
}

