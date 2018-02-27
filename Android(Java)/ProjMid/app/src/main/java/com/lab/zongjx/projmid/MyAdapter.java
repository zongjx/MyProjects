package com.lab.zongjx.projmid;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.ViewGroup;

import java.util.List;


public abstract class MyAdapter<T> extends RecyclerView.Adapter<MyViewHolder> {
    private Context context;
    private List<T> list;
    private int layoutId;
    private OnItemClickListener mOnItemClickListener = null;

    public MyAdapter(Context context, int layoutId, List<T> list) {
        this.context = context;
        this.list = list;
        this.layoutId = layoutId;
    }

    @Override
    public MyViewHolder onCreateViewHolder(final ViewGroup parent, int viewType) {
        MyViewHolder myViewHolder = MyViewHolder.get(context, parent, layoutId);
        myViewHolder.mOnItemClickListener = mOnItemClickListener;
        return myViewHolder;
    }

    @Override
    public void onBindViewHolder(final MyViewHolder holder, int position) {
        convert(holder, list.get(position));

        if(mOnItemClickListener != null) {
            holder.itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    mOnItemClickListener.onClick(holder.getAdapterPosition());
                }
            });
            holder.itemView.setOnLongClickListener(new View.OnLongClickListener(){
                @Override
                public boolean onLongClick(View v){
                    mOnItemClickListener.onLongClick(holder.getAdapterPosition());
                    return false;
                }
            });
        }
    }

    public abstract void convert(MyViewHolder holder,T t);

    @Override
    public int getItemCount(){
        return list.size();
    }

    public void removeItem(int position){
        list.remove(position);
        notifyItemRemoved(position);
    }

    public interface OnItemClickListener{
        void onClick(int position);
        void onLongClick(int position);
        void onItemClick(int position,View view);
    }

    public void setOnItemClickListener(OnItemClickListener onItemClickListener) {
        this.mOnItemClickListener = onItemClickListener;
    }

    public T getItem(int i){
        if(list == null) {
            return null;
        }
        return list.get(i);
    }
}
